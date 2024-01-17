#pragma once

#include "Node.h"
#include "AllOperators.h"
#include "../h/NodeTypes/BinaryNode.h"
#include "../h/NodeTypes/CompoundNode.h"
#include "../h/NodeTypes/UnaryNode.h"
#include "../h/NodeTypes/FunctionNode.h"
#include "../h/NodeTypes/NullNode.h"

#include "FunctionModes/Immediate.h"
#include "FunctionModes/Conditional.h"
#include "FunctionModes/Regular.h"

class Parser {
public:
	Parser(vector<Token>& tokens);

	bool Done() {
		return _currTokenIndex >= _tokens.size() - 1;
	}

	Node* Parse();

private:
	ModeData FunctionCondition();

	CompoundNode* FunctionArguments();

	ModeData FunctionModifier();

	string FunctionHeader(ModeData& mode);

	Node* FunctionBody();

	Node* FunctionReturn();

	Node* Function();


	Node* Primary();

	Node* UnaryExpression();

	Node* Expression(int minPrecedence = INT_MAX);

	Node* Statement();

	CompoundNode* Statements(function<bool()>);

private:
	int _currTokenIndex = 0;

	vector<Token>& _tokens;

	const Token GetCurrent();

	Token Match(Token::Type expectedType);

	void RemoveIfLineEnd() {
		if (GetCurrent().GetType() == Token::LINE_END)
			_currTokenIndex++;
	}

	bool Assert(Token token, string text) const;

	static bool SearchOperator(Token opToken, Operator& op, Operator::InputTaken input);
};



