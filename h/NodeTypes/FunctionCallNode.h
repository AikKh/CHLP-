#pragma once

#include "../Node.h"
#include "CompoundNode.h"

namespace Doer {

	class FunctionCallNode : public Node {
	public:
		FunctionCallNode(Node* value, Node* args) : m_value(value), m_args(args) {}

		~FunctionCallNode() override {
			delete m_value;
			delete m_args;
		}

		void Print(int level = 0) const override {
			string ind = string(level, ' ');

			cout << ind << "Function call: " << endl;
			m_value->Print(level + Indedention);

			cout << ind << "Arguments: " << endl;
			m_args->Print(level + Indedention);
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

		const Node* GetValue() const
		{
			return m_value;
		}

		const Node* GetArgs() const
		{
			return m_args;
		}

	private:
		// Value can be another function call, so it's typed Node* 
		Node* m_value;
		Node* m_args;
	};
}