#pragma once

#include "../Node.h"

namespace Doer {

	class NullNode : public Node {
	public:
		~NullNode() override = default;

		ActionNode* Accept(ActionTreeGenerator&) const override;

		void Print(int level = 0) const override {
			cout << string(level, ' ') << "NULL Node" << endl;
		}
	};
}