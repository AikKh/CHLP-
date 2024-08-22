#pragma once

#include "../ActionNode.h"

namespace Doer {

	class ListAction : public ActionNode {
	public:
		// TODO: change logic: return value 
		Object Execute() const override { 
			for (const auto& action : actions) {
				action->Execute();

				if (!error.IsOk()) {
					return Object::None();
				}
			}

			return Object::None();
		}

		void AddAction(unique_ptr<ActionNode> action) {
			actions.push_back(move(action));
		}

	private:
		vector<unique_ptr<ActionNode>> actions;
	};
}
