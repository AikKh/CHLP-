#pragma once

#include "../ActionNode.h"

namespace Doer {

	class NoAction : public ActionNode {
	public:
		Object Execute() const override {
			return Object::None();
		}
	};
}
