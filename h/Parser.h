#pragma once

#include "Node.h"
#include "AllOperators.h"

#include "NodeTypes/BinaryNode.h"
#include "NodeTypes/CompoundNode.h"
#include "NodeTypes/UnaryNode.h"
#include "NodeTypes/FunctionNode.h"
#include "NodeTypes/NullNode.h"
#include "NodeTypes/FunctionCallNode.h"
#include "NodeTypes/IfNode.h"
#include "NodeTypes/ReturnNode.h"

namespace Doer {

	class Parser {
	public:
		Parser(vector<Token>& tokens);

		bool Done() {
			return _currTokenIndex >= _tokens.size() - 1;
		}

		CompoundNode* Parse();

	private:
		CompoundNode* ParseList(function<Node* ()>, const string& begin, const string& end);

		CompoundNode* CallArguments();

		CompoundNode* FunctionArguments();

		string FunctionHeader();

		CompoundNode* FunctionBody();

		Node* Function();

		Node* LookForCall(Node*);

		Node* Primary();

		Node* UnaryExpression();

		Node* Expression(int maxPrecedence = INT_MAX);

		Node* ConditionalStatement();

		Node* ReturnStatement();

		Node* Statement();

		CompoundNode* Statements(function<bool()>);

	private:
		int _currTokenIndex = 0;

		// TODO: Change vector to queue
		vector<Token>& _tokens;

		const Token& GetCurrent();

		Token Match(Token::Type expectedType);

		bool Assert(const Token& token, const string& text) const;

		static bool SearchOperator(const Token& opToken, Operator& op, Operator::InputTaken input);
	};
}


