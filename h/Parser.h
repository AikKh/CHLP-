#pragma once

#include "Node.h"
#include "AllOperators.h"
#include "../h/NodeTypes/BinaryNode.h"
#include "../h/NodeTypes/CompoundNode.h"
#include "../h/NodeTypes/UnaryNode.h"
#include "../h/NodeTypes/FunctionNode.h"
#include "../h/NodeTypes/NullNode.h"
#include "../h/NodeTypes/FunctionCallNode.h"

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
	CompoundNode* ParseList(function<Node* ()>);

	CompoundNode* CallArguments();

	CompoundNode* FunctionArguments();

	ModeData FunctionCondition();

	ModeData FunctionModifier();

	string FunctionHeader(ModeData& mode);

	Node* FunctionBody();

	Node* FunctionReturn();

	Node* Function();

	Node* LookForCall(Node*);

	Node* Primary();

	Node* UnaryExpression();

	Node* Expression(int maxPrecedence = INT_MAX);

	Node* Statement();

	CompoundNode* Statements(function<bool()>);

private:
	int _currTokenIndex = 0;

	vector<Token>& _tokens;

	const Token GetCurrent();

	Token Match(Token::Type expectedType);

	bool Assert(Token token, string text) const;

	static bool SearchOperator(Token opToken, Operator& op, Operator::InputTaken input);
};



