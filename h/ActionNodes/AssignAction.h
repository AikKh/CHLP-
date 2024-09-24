#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer 
{
	class AssignAction : public ActionNode {
	public:
		AssignAction(shared_ptr<Stack> stack, const string& id, ActionNode* right) :
			_stack{ std::move(stack) }, _id{ id }, _right{ right }
		{} 

		shared_ptr<Object> Execute() const override {
			shared_ptr<Object> obj = _right->Execute();
			_stack->Set(_id, obj);

			return obj;
		}

	private:
		shared_ptr<Stack> _stack;
		const string& _id;
		unique_ptr<ActionNode> _right;
	};
}
