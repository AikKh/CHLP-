#pragma once

#include "LeafNode.h"

namespace Doer {

	class UnaryNode : public LeafNode {
	public:
		UnaryNode(Token value, Node* next = nullptr) : LeafNode(move(value)), _next(next) {};

		~UnaryNode() override {
			delete _next;
		}

		void Print(int level = 0) const override {
			LeafNode::Print(level);
			_next->Print(level + Indedention);
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

	private:
		Node* _next;
	};
}