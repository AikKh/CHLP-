#include "../../h/ActionNodes/CompoundAction.h"
#include "../../h/ActionNodes/IfAction.h"
#include "../../h/ActionNodes/ReturnAction.h"
#include "../../h/MemoryManagement/StackFrame.h"
#include "../../h/MemoryManagement/ObjectGenerator.h"

namespace Doer
{
    Object::ObjectPtr Doer::CompoundAction::ExecuteWithReturn(shared_ptr<Stack> stack) const
	{
		bool returned = false;

		for (const auto& action : actions)
		{
			auto res = action->Execute();

			if (dynamic_cast<ReturnAction*>(action.get()))
			{
				return res;
			}
			else if (dynamic_cast<IfAction*>(action.get()))
			{
				if (res)
				{
					return res;
				}
			}

			if (!error.IsOk())
			{
				return nullptr;
			}
		}

		stack->Close();
		return ObjectGenerator::GenerateNone();
	}
}

