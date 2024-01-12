#pragma once

#include "../Node.h"

class UnaryNode : public Node {

public:
	UnaryNode(Token value, Node* next = nullptr) : Node(value), _next(next) {}

	~UnaryNode() {
		delete _next;
	}

	void Print(int level = 0) override {
		Node::Print(level);
		_next->Print(level + Indedention);
	}

private:
	Node* _next;
};