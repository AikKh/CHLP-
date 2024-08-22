#pragma once

#include "../Node.h"

namespace Doer {

	class CompoundNode : public Node {
	public:

		~CompoundNode() override {
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

		ActionNode* Accept(Visitor& runner) const override;

	private:
		vector<Node*> nodes;

		friend class ActionTreeGenerator;
	};
}