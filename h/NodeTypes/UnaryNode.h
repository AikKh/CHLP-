#pragma once

#include "LeafNode.h"

class UnaryNode : public LeafNode {

public:
	UnaryNode(Token value, Node* next = nullptr) : LeafNode(value), _next(next) {}

	~UnaryNode() {
		delete _next;
	}

	void Print(int level = 0) const override {
		LeafNode::Print(level);
		_next->Print(level + Indedention);
	}

private:
	Node* _next;
};