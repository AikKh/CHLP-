#pragma once

#include "../Node.h"
#include "CompoundNode.h"

class FunctionCallNode : public Node {
public:
	FunctionCallNode(Node* value, Node* args = nullptr) : _value(value), _args(args) {}

	~FunctionCallNode() {
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

private:
	Node* _value;
	Node* _args;
};