#include "../h/Parser.h"

namespace Doer {

	Doer::Parser::Parser(vector<Token>& tokens) : _tokens(tokens) {}

	const Doer::Token& Doer::Parser::GetCurrent()
	{
		return _tokens[_currTokenIndex];
	}

	Doer::Token Doer::Parser::Match(Token::Type expectedType)
	{
		const Token curr = GetCurrent();

		if (curr.GetType() == expectedType) {
			_currTokenIndex++;
			return curr;
		}
		error.ReportAt("Unexpected token: " + curr.GetText(), ErrorPriority::SOURCE_ERROR, curr.Line, curr.Column);

		return Token::Default();
	}

	bool Doer::Parser::Assert(const Token& token, const string& text) const
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

	bool Doer::Parser::SearchOperator(const Token& opToken, Operator& op, Operator::InputTaken input)
	{
		if (!operators.SearchOperator(opToken.GetText(), op, input)) {
			error.ReportAt("Unrecognized operator " + opToken.GetText(), ErrorPriority::SOURCE_ERROR, opToken.Line, opToken.Column);
			return false;
		}
		return true;
	}

#pragma region Function

	Doer::CompoundNode* Doer::Parser::ParseList(function<Node* ()> getItem, const string& begin, const string& end)
	{
		Assert(Match(Token::SCOPE), begin);

		CompoundNode* res = new CompoundNode();

		if (GetCurrent().Equals(Token::SCOPE, end)) {
			Match(Token::SCOPE);
			return res;
		}

		res->AddNode(getItem());

		while (!GetCurrent().Equals(Token::SCOPE, end) && error.IsOk()) {
			Assert(Match(Token::COMMA), ",");

			res->AddNode(getItem());
		}

		Assert(Match(Token::SCOPE), end);
		return res;
	}

	// TODO: fix code repetition in CallArguments and FunctionArguments
	Doer::CompoundNode* Doer::Parser::CallArguments()
	{
		return ParseList([this]() {
			return Expression();
			}, "(", ")");
	}

	Doer::CompoundNode* Doer::Parser::FunctionArguments()
	{
		return ParseList([this]() {
			return new LeafNode(Match(Token::IDENTIFIER));
			}, "[", "]");
	}

	string Doer::Parser::FunctionHeader()
	{
		Assert(Match(Token::SCOPE), "[");

		string id = Match(Token::IDENTIFIER).GetText();

		Assert(Match(Token::SCOPE), "]");

		return id;
	}

	Doer::CompoundNode* Doer::Parser::FunctionBody()
	{
		Assert(Match(Token::SCOPE), "{");

		if (GetCurrent().Equals(Token::SCOPE, "}")) {
			Match(Token::SCOPE);
			return new CompoundNode();
		}

		CompoundNode* res = Statements([this]() {
			return !(GetCurrent().Equals(Token::SCOPE, "}"));
		});

		Assert(Match(Token::SCOPE), "}");

		return res;
	}

	Doer::Node* Doer::Parser::Function()
	{
		string id = FunctionHeader();
		CompoundNode* args = FunctionArguments();

		CompoundNode* body = FunctionBody();

		return new FunctionNode(id, args, body);
	}

	Doer::Node* Doer::Parser::LookForCall(Node* value)
	{
		if (GetCurrent().Equals(Token::SCOPE, "(")) {
			auto call = new FunctionCallNode(value, CallArguments());
			return LookForCall(call);
		}
		return value;
	}

#pragma endregion

#pragma region Expression

	// TODO: Add function call option
	Doer::Node* Doer::Parser::Primary()
	{
		Token curr = GetCurrent();

		// Change IDENTIFIER matching logic to fit function calling
		if (curr.GetType() == Token::LITERAL) {
			Match(Token::LITERAL);
			return new LeafNode(curr);
		}
		else if (curr.GetType() == Token::IDENTIFIER) {
			Node* id = new LeafNode(Match(Token::IDENTIFIER));
			return LookForCall(id);
		}
		else if (curr.GetType() == Token::BOOLEAN) {
			Match(Token::BOOLEAN);
			return new LeafNode(curr);
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

	Doer::Node* Doer::Parser::UnaryExpression()
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

	Doer::Node* Doer::Parser::Expression(int maxPrecedence)
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

#pragma region Keywords

	Node* Parser::ConditionalStatement()
	{
		Match(Token::Type::KEYWORD); // if

		vector<Node*> conditions;
		vector<Node*> bodies;
		
		conditions.push_back(Expression());
		bodies.push_back(FunctionBody());

		while (GetCurrent().Equals(Token::KEYWORD, "elif"))
		{
			Match(Token::Type::KEYWORD);
			conditions.push_back(Expression());
			bodies.push_back(FunctionBody());
		}

		Node* else_body = nullptr;
		if (GetCurrent().Equals(Token::KEYWORD, "else"))
		{
			Match(Token::Type::KEYWORD);
			else_body = FunctionBody();
		}

		return new IfNode(std::move(conditions), std::move(bodies), else_body);
	}

	Node* Parser::ReturnStatement()
	{
		Match(Token::Type::KEYWORD);

		Node* value = Expression();
		Match(Token::LINE_END);

		return new ReturnNode(value);
	}

#pragma endregion

	Doer::Node* Doer::Parser::Statement()
	{
		Token curr = GetCurrent();

		if (curr.Equals(Token::SCOPE, "[")) {
			return Function();
		}
		else if (curr.Equals(Token::LINE_END, ";")) { // Just empty line
			Match(Token::LINE_END);
			return new NullNode();
		}
		else if (curr.Equals(Token::KEYWORD, "if")) {
			return ConditionalStatement();
		}
		else if (curr.Equals(Token::KEYWORD, "return")) {
			return ReturnStatement();
		}

		auto res = Expression();
		Match(Token::LINE_END);
		return res;
	}

	Doer::CompoundNode* Doer::Parser::Statements(function<bool()> parseUntil)
	{
		CompoundNode* nodes = new CompoundNode();

		Node* statement = Statement();
		nodes->AddNode(statement);

		auto t = GetCurrent();

		while (parseUntil() && error.IsOk()) {

			while (GetCurrent().Equals(Token::LINE_END, ";")) {
				Match(Token::LINE_END);
			}

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

	CompoundNode* Doer::Parser::Parse() {
		CompoundNode* res = Statements([this]() {
			return !Done();
		});
		Match(Token::END_OF_FILE);
		return res;
	}
}