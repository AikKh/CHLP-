#pragma once

#include "../Node.h"

class ListNode : public Node {

public:
	ListNode(string text) : Node(Token(Token::Type::UNKNOWN, text)) {}

	~ListNode() {
		for (auto& node : nodes) {
			delete node;
		}
	}

	void Print(int level = 0) override {
		Node::Print(level);
		
		for (auto& node : nodes) {
			node->Print(level + Indedention);
		}
	}

	void AddNode(Node* node) {
		nodes.push_back(node);
	}

private:
	vector<Node*> nodes;
};