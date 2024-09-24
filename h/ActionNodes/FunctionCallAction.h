#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer
{
	class FunctioCallAction : public ActionNode {
	public:
		FunctioCallAction(shared_ptr<Stack> stack, unique_ptr<ActionNode> get_func, vector<unique_ptr<ActionNode>> args) :
			m_stack{ std::move(stack) }, m_get_func{ std::move(get_func) }, m_args{ std::move(args) }
		{}

		shared_ptr<Object> Execute() const override
		{
			vector<Object::ObjectPtr> resolved_args;

			for (auto& arg : m_args)
			{
				resolved_args.push_back(arg->Execute());
			}

			auto func = m_get_func->Execute();

			if (!func)
			{
				error.Report("Got error while calling function", ErrorPriority::RUNTIME_ERROR);
				return nullptr;
			}

			m_stack->Open();
			return func->CallMethod(MethodType::CALL, std::move(resolved_args));
		}

	private:
		shared_ptr<Stack> m_stack;
		unique_ptr<ActionNode> m_get_func;
		vector <unique_ptr< ActionNode >> m_args;
	};
}
