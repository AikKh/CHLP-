#pragma once

#include "../ActionNode.h"

namespace Doer {

	class CompoundAction : public ActionNode {
	public:
		// TODO: change logic: return value 
		shared_ptr<Object> Execute() const override {
			for (const auto& action : actions) {
				action->Execute();

				if (!error.IsOk()) {
					return nullptr;
				}
			}

			return nullptr;
		}

		Object::ObjectPtr ExecuteWithReturn(shared_ptr<Stack> stack) const;

		void AddAction(unique_ptr<ActionNode> action) {
			actions.push_back(move(action));
		}

	private:
		vector<unique_ptr<ActionNode>> actions;
	};
}
