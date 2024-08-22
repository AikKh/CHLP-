#pragma once

#include "../Node.h"
#include "CompoundNode.h"

namespace Doer {

	class FunctionCallNode : public Node {
	public:
		FunctionCallNode(Node* value, Node* args = nullptr) : _value(value), _args(args) {}

		~FunctionCallNode() override {
			delete _value;
			delete _args;
		}

		void Print(int level = 0) const override {
			string ind = string(level, ' ');

			cout << ind << "Function call: " << endl;
			_value->Print(level + Indedention);

			cout << ind << "Arguments: " << endl;
			_args->Print(level + Indedention);
		}

		ActionNode* Accept(Visitor& runner) const override;

	private:
		// Value can be another function call, so it's typed Node* 
		Node* _value;
		Node* _args;
	};
}