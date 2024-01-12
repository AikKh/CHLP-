#include "../h/Parser.h"

Parser::Parser(vector<Token>& tokens) : _tokens(tokens) {}

const Token Parser::GetCurrent()
{
	return _tokens[_currTokenIndex];
}

Token Parser::Match(Token::Type expectedType)
{
	const Token curr = GetCurrent();

	if (curr.GetType() == expectedType) {
		_currTokenIndex++;
		return curr;
	}
	error.ReportAt("Unexpected token: " + curr.GetText(), ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);
}

bool Parser::SearchOperator(Token opToken, Operator& op, Operator::InputTaken input)
{
	if (!operators.FindOperatorByText(opToken.GetText(), op, input)) {
		error.ReportAt("Unrecognized operator " + opToken.GetText(), ErrorPriority::SOURCE_ERROR, opToken.Line, opToken.Column);
		return false;
	}
	return true;
}

// Main parser logic

#pragma region Expression
//
//Node* Parser::MultExpression()
//{
//	Node* left = Primary();
//
//	string currText = GetCurrent().GetText();
//
//	while (!Done() && (currText == "*" || currText == "/")) {
//		Token op = Match(Token::Type::OPERATOR);
//		Node* right = Primary();
//
//		left = new BinaryNode(op, left, right);
//		currText = GetCurrent().GetText();
//	}
//
//	return left;
//}
//
//Node* Parser::AddExpression()
//{
//	// TODO: increase readability
//
//	Node* left = MultExpression();
//
//	string currText = GetCurrent().GetText();
//
//	while (!Done() && (currText == "+" || currText == "-")) {
//		Token op = Match(Token::Type::OPERATOR);
//		Node* right = MultExpression();
//
//		left = new BinaryNode(op, left, right);
//		currText = GetCurrent().GetText();
//	}
//
//	return left;
//}
//
//Node* Parser::ComparisonExpression()
//{
//	Node* left = AddExpression();
//
//	string currText = GetCurrent().GetText();
//
//	while (!Done() && (currText == ">" || currText == "<" || currText == ">=" || currText == "<=")) {
//		Token op = Match(Token::Type::OPERATOR);
//		Node* right = AddExpression();
//
//		left = new BinaryNode(op, left, right);
//		currText = GetCurrent().GetText();
//	}
//
//	return left;
//}
//
//Node* Parser::EqualExpression()
//{
//	Node* left = ComparisonExpression();
//
//	string currText = GetCurrent().GetText();
//
//	while (!Done() && (currText == "==" || currText == "!=")) {
//		Token op = Match(Token::Type::OPERATOR);
//		Node* right = ComparisonExpression();
//
//		left = new BinaryNode(op, left, right);
//		currText = GetCurrent().GetText();
//	}
//
//	return left;
//}

Node* Parser::Primary()
{
	Token curr = GetCurrent();

	if (curr.GetType() == Token::Type::LITERAL || curr.GetType() == Token::Type::IDENTIFIER) {
		Match(curr.GetType());
		return new Node(curr);
	}

	// TODO: add opening and closing checking
	else if (curr.GetType() == Token::Type::SCOPE) {
		Match(Token::Type::SCOPE);
		Node* res = Expression();
		Match(Token::Type::SCOPE);

		return res;
	}

	// TODO: Move to Unary
	

	error.ReportAt("Unexpected token: " + curr.GetText(), ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);
	return nullptr;
}

Node* Parser::UnaryExpression()
{
	Token curr = GetCurrent();

	if (curr.GetType() == Token::Type::OPERATOR) {
		Token opToken = Match(Token::Type::OPERATOR);

		Operator op;
		if (!SearchOperator(opToken, op, Operator::RIGHT)) {
			return nullptr;
		}

		Node* next = UnaryExpression();
		return new UnaryNode(opToken, next);
	}
	return Primary();
}

Node* Parser::Expression(int minPrecedence)
{
	Node* left = UnaryExpression();

	while (GetCurrent().GetType() == Token::Type::OPERATOR) {

		Token opToken = GetCurrent();

		// Finding operator in operator table
		/*bool found = false;
		Operator op = operators.FindOperatorByText(opToken.GetText(), found);

		if (!found) {
			error.ReportAt("Unrecognized operator " + opToken.GetText(), ErrorPriority::SOURCE_ERROR, opToken.Line, opToken.Column);
			break;
		}*/
		Operator op;

		if (!SearchOperator(opToken, op, Operator::BOTH)) {
			break;
		}
		if (op.GetPrecedence() > minPrecedence) {
			break;
		}

		Match(Token::Type::OPERATOR);

		int precedence = op.GetPrecedence();
		
		// There was a derivation problem, -1 fixed it
		// (I don't fully understand how it works)
		Node* right = Expression(precedence - 1);

		left = new BinaryNode(opToken, left, right);
	}

	return left;
}

#pragma endregion

Node* Parser::Assignment()
{
	// TODO: increase readability

	Token id = Match(Token::Type::IDENTIFIER);
	Token op = GetCurrent();

	if (op.GetType() == Token::Type::OPERATOR && op.GetText() == "=") {
		Match(Token::Type::OPERATOR);

		return new BinaryNode(op, new Node(id), Expression());
	}

	error.ReportAt("Expected assign operator", ErrorPriority::SOURCE_ERROR, op.Line, op.Column);
	return nullptr;
}

Node* Parser::Statement()
{
	Token curr = GetCurrent();
	Token::Type currType = curr.GetType();

	if (currType == Token::Type::IDENTIFIER) {
		return Assignment();
	}
	else if (currType == Token::Type::SCOPE) {
		// Function handling
	}
	// Must be expression
	else {
		return Expression();
	}

	error.ReportAt("Expected identifier", ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);
	return nullptr;
}

Node* Parser::Statements()
{
	ListNode* nodes = new ListNode("Program:");

	while (!Done()) {
		Node* statement = Statement();

		if (!statement) {
			Token curr = GetCurrent();
			error.ReportAt("Can't pasre line", ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);
			break;
		}

		nodes->AddNode(statement);

		Match(Token::Type::LINE_END);
	}

	return nodes;
}

Node* Parser::Parse() {
	Node* res = Statements();
	Match(Token::Type::END_OF_FILE);
	return res;
}