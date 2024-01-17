#pragma once

#include "LeafNode.h"

class BinaryNode : public LeafNode {
public:
	// friend struct Token;

	BinaryNode(Token value, Node* left = nullptr, Node* right = nullptr) : LeafNode(value), _left(left), _right(right) {}

	~BinaryNode() {
		if (_left != nullptr) {
			delete _left;
		}

		if (_right != nullptr) {
			delete _right;
		}
	}

	void Print(int level = 0) const override {
		LeafNode::Print(level);
		if (_left)
			_left->Print(level + Indedention);
		if (_right)
			_right->Print(level + Indedention);
	}

private:

	Node* _left;
	Node* _right;
};