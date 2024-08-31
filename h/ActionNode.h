#pragma once

#include "MemoryManagement/StackFrame.h"

namespace Doer {

	class ActionNode {
	public:
		virtual ~ActionNode() = default;
		virtual shared_ptr<Object> Execute() const = 0;
	};
}
