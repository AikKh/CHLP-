#pragma once

#include "MemoryManagement/StackFrame.h"

namespace Doer {

	class ActionNode {
	public:
		virtual ~ActionNode() = default;
		virtual Object Execute() const = 0;
	};
}
