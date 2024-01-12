#pragma once

#include "Node.h"
#include "AllOperators.h"
#include "../h/NodeTypes/BinaryNode.h"
#include "../h/NodeTypes/ListNode.h"
#include "../h/NodeTypes/UnaryNode.h"

class Parser {
public:
	Parser(vector<Token>& tokens);

	bool Done() {
		return _currTokenIndex >= _tokens.size() - 1;
	}

	Node* Parse();

private:

	Node* Primary();

	Node* UnaryExpression();

	Node* Expression(int minPrecedence = operators.MaxPrecedence);

	Node* Statement();

	Node* Statements();

	Node* Assignment();


private:
	int _currTokenIndex = 0;

	vector<Token>& _tokens;

	const Token GetCurrent();

	Token Match(Token::Type expectedType);

	static bool SearchOperator(Token opToken, Operator& op, Operator::InputTaken input);
};



