#pragma once

#include "../Node.h"

class BinaryNode : public Node {
public:
	// friend struct Token;

	BinaryNode(Token value, Node* left = nullptr, Node* right = nullptr) : Node(value), _left(left), _right(right) {}

	~BinaryNode() {
		if (_left != nullptr) {
			delete _left;
		}

		if (_right != nullptr) {
			delete _right;
		}
	}

	void Print(int level = 0) override {
		Node::Print(level);
		if (_left)
			_left->Print(level + Indedention);
		if (_right)
			_right->Print(level + Indedention);
	}

	/*const Token& GetValue() const {
		return Node::_value;
	}

	Node* GetLeft() {
		return _left;
	}

	Node* GetRight() {
		return _right;
	}

	void SetValue(Token value) {
		Node::_value = value;
	}*/

private:

	Node* _left;
	Node* _right;
};