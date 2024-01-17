#pragma once

#include "../Node.h"

class CompoundNode : public Node {

public:

	~CompoundNode() {
		for (auto& node : nodes) {
			delete node;
		}
	}

	void Print(int level = 0) const override {
		cout << string(level, ' ') << "Compound node:" << endl;

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