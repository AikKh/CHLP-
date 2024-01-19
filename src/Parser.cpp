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

	return Token::Default();
}

bool Parser::Assert(Token token, string text) const
{
	if (token.GetText() != text) {
		string msg = "Expected a " + text;

		if (token.GetType() != Token::UNKNOWN)
			msg += " got " + token.GetText();

		error.Report(msg, ErrorPriority::SOURCE_ERROR);
		return false;
	}
	return true;
}

bool Parser::SearchOperator(Token opToken, Operator& op, Operator::InputTaken input)
{
	if (opToken.GetText() == ",") {
		int a = 5;
	}
	if (!operators.FindOperatorByText(opToken.GetText(), op, input)) {
		error.ReportAt("Unrecognized operator " + opToken.GetText(), ErrorPriority::SOURCE_ERROR, opToken.Line, opToken.Column);
		return false;
	}
	return true;
}

#pragma region Function

CompoundNode* Parser::ParseList(function<Node* ()> getItem)
{
	Assert(Match(Token::SCOPE), "[");

	CompoundNode* res = new CompoundNode();

	if (GetCurrent().Equals(Token::SCOPE, "]")) {
		Match(Token::SCOPE);
		return res;
	}

	res->AddNode(getItem());

	while (!GetCurrent().Equals(Token::SCOPE, "]") && error.IsOk()) {
		Assert(Match(Token::COMMA), ",");

		res->AddNode(getItem());
	}

	Assert(Match(Token::SCOPE), "]");
	return res;
}

// TODO: fix code repetition in CallArguments and FunctionArguments
CompoundNode* Parser::CallArguments()
{
	return ParseList([this]() {
		return Expression();
	});
}

CompoundNode* Parser::FunctionArguments() 
{
	return ParseList([this]() {
		return new LeafNode(Match(Token::IDENTIFIER));
	});
}

ModeData Parser::FunctionCondition()
{
	Assert(Match(Token::SCOPE), "[");
	Node* expr = Expression();
	Assert(Match(Token::SCOPE), "]");

	return Conditional(expr);
}

ModeData Parser::FunctionModifier()
{
	Token mode = Match(Token::OPERATOR);
	
	if (mode.GetText().size() != 1) {
		error.ReportAt("Expected a modifier (! or ?)", ErrorPriority::SOURCE_ERROR, mode.Line, mode.Column);
	}

	Assert(Match(Token::SCOPE), "]");

	switch (mode.GetText()[0])
	{
	case '!':
		return Immediate();
	case '?':
		return FunctionCondition();

	default:
		error.ReportAt("Unexpected modifier " + mode.GetText(), ErrorPriority::SOURCE_ERROR, mode.Line, mode.Column);
	}
}

string Parser::FunctionHeader(ModeData& mode)
{
	Assert(Match(Token::SCOPE), "[");

	string id = "";

	Token curr = GetCurrent();

	if (curr.GetType() == Token::IDENTIFIER) {
		id = Match(Token::IDENTIFIER).GetText();
		curr = GetCurrent();
	}

	if (curr.GetType() == Token::OPERATOR) {
		mode = FunctionModifier();
	}
	else if (curr.GetType() == Token::SCOPE) {
		Assert(Match(Token::SCOPE), "]");
		
		CompoundNode* args = nullptr;

		if (GetCurrent().Equals(Token::SCOPE, "[")) {
			args = FunctionArguments();
		}

		mode = Regular(args);
	}

	return id;
}

Node* Parser::FunctionBody()
{
	Assert(Match(Token::SCOPE), "{");

	if (GetCurrent().Equals(Token::SCOPE, "}")) {
		Match(Token::SCOPE);
		return new NullNode();
	}

	CompoundNode* res = Statements([this](){
		return !(GetCurrent().Equals(Token::SCOPE, "}"));
	});
	Assert(Match(Token::SCOPE), "}");

	return res;
}

Node* Parser::FunctionReturn()
{
	Assert(Match(Token::SCOPE), "(");

	if (GetCurrent().Equals(Token::SCOPE, ")")) {
		Match(Token::SCOPE);
		return new NullNode();
	}

	Node* res = Expression();
	Assert(Match(Token::SCOPE), ")");

	return res;
}

Node* Parser::Function()
{
	ModeData mode;
	string id = FunctionHeader(mode);

	Node* body = nullptr;
	Node* ret = nullptr;

	if (GetCurrent().Equals(Token::SCOPE, "{")) {
		body = FunctionBody();
	}
	if (GetCurrent().Equals(Token::SCOPE, "(")) {
		ret = FunctionReturn();
	}

	return new FunctionNode(id, mode, body, ret);
}

Node* Parser::LookForCall(Node* value)
{
	if (GetCurrent().Equals(Token::SCOPE, "[")) {
		auto call = new FunctionCallNode(value, CallArguments());
		return LookForCall(call);
	}
	return value;
}

#pragma endregion

#pragma region Expression

// TODO: Add function call option
Node* Parser::Primary()
{
	Token curr = GetCurrent();

	// Change IDENTIFIER matching logic to fit function calling
	if (curr.GetType() == Token::LITERAL) {
		Match(curr.GetType());
		return new LeafNode(curr);
	}
	else if (curr.GetType() == Token::IDENTIFIER) {
		Node* id = new LeafNode(Match(Token::IDENTIFIER));
		return LookForCall(id);
	}

	else if (Assert(Match(Token::SCOPE), "(")) {
		Node* res = Expression();

		Assert(Match(Token::SCOPE), ")");
		return res;
	}

	error.ReportAt("Unexpected token: " + curr.GetText() + " expected a value", 
		ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);
	return new NullNode();
}

Node* Parser::UnaryExpression()
{
	Token curr = GetCurrent();

	if (curr.GetType() == Token::OPERATOR) {
		Token opToken = Match(Token::OPERATOR);

		Operator op;
		if (!SearchOperator(opToken, op, Operator::RIGHT)) {
			return new NullNode();
		}

		Node* next = UnaryExpression();
		return new UnaryNode(opToken, next);
	}
	return Primary();
}

Node* Parser::Expression(int maxPrecedence)
{
	Node* left = UnaryExpression();

	while (GetCurrent().GetType() == Token::OPERATOR) {

		Token opToken = GetCurrent();

		Operator op;

		if (!SearchOperator(opToken, op, Operator::BOTH)) {
			break;
		}
		else if (op.GetPrecedence() > maxPrecedence) {
			break;
		}

		Match(Token::Type::OPERATOR);

		int precedence = op.GetAssociativity() == Operator::Associativity::LEFT ? op.GetPrecedence() - 1 : op.GetPrecedence();
		
		Node* right = Expression(precedence);

		left = new BinaryNode(opToken, left, right);
	}

	return left;
}

#pragma endregion

Node* Parser::Statement()
{
	Token curr = GetCurrent();

	if (curr.Equals(Token::SCOPE, "[")) {
		return Function();
	}

	auto res = Expression();
	Match(Token::LINE_END);
	return res;
}

CompoundNode* Parser::Statements(function<bool()> parseUntil)
{
	CompoundNode* nodes = new CompoundNode();

	Node* statement = Statement();
	nodes->AddNode(statement);

	auto t = GetCurrent();

	while (parseUntil() && error.IsOk()) {

		statement = Statement();

		if (!statement) {
			Token curr = GetCurrent();
			error.ReportAt("Can't pasre line", ErrorPriority::SOURCE_ERROR, curr.Line, 0);
			break;
		}

		nodes->AddNode(statement);
	}

	return nodes;
}

Node* Parser::Parse() {
	Node* res = Statements([this]() {
		return !Done();
	});
	Match(Token::END_OF_FILE);
	return res;
}