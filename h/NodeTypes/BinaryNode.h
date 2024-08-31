#pragma once

#include "LeafNode.h"

namespace Doer {

	class BinaryNode : public LeafNode {
	public:
		// friend struct Token;

		BinaryNode(Token value, Node* left = nullptr, Node* right = nullptr) : LeafNode(move(value)), _left(left), _right(right) {}

		~BinaryNode() override {
			delete _left;
			delete _right;
		}

		const Token& GetValue() const {
			return LeafNode::GetValue();
		}

		const Node* GetLeft() const {
			return _left;
		}

		const Node* GetRight() const {
			return _right;
		}

		void Print(int level = 0) const override {
			LeafNode::Print(level);
			if (_left)
				_left->Print(level + Indedention);
			if (_right)
				_right->Print(level + Indedention);
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

	private:

		Node* _left;
		Node* _right;
	};
}