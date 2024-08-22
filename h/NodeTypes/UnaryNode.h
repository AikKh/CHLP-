#pragma once

#include "LeafNode.h"

namespace Doer {

	class UnaryNode : public LeafNode {
	public:
		UnaryNode(Token value, Node* next = nullptr) : LeafNode(move(value)), _next(next) {};

		~UnaryNode() override {
			delete _next;
		}

		ActionNode* Accept(Visitor& runner) const override;

		void Print(int level = 0) const override {
			LeafNode::Print(level);
			_next->Print(level + Indedention);
		}

	private:
		Node* _next;
	};
}