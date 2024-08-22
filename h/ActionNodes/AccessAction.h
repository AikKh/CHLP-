#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer {

	class AccessAction : public ActionNode {
	public:
		AccessAction(StackFrame& stack, const string& id) :
			_stack{ stack }, _id{ id }
		{}

		Object Execute() const override {
			auto [type, address] = _stack.GetInfo(_id);
			const void* ptr = _stack.GetPtrByStackAddress(address);

			return Object::Copy(type, ptr); // a = b would be always by value. May change this in the future
		}

	private:
		StackFrame& _stack;
		const string& _id;
	};
}
