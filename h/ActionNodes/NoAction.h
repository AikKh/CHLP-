#pragma once

#include "../ActionNode.h"

namespace Doer {

	class NoAction : public ActionNode {
	public:
		// Why is it even here?
		shared_ptr<Object> Execute() const override {
			return nullptr;
		}
	};
}
