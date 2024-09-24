#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/ObjectGenerator.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer
{
	class ReturnAction : public ActionNode {
	public:
		ReturnAction(ActionNode* expression, shared_ptr<Stack> stack) : m_expression{ expression }, m_stack{ std::move(stack) } {}

		shared_ptr<Object> Execute() const override
		{
			if (m_expression)
			{
				if (const_cast<const Stack*>(m_stack.get())->GetPrevious() == nullptr)
				{
					error.Report("Cannot return in global namespace", ErrorPriority::RUNTIME_ERROR);
					return nullptr;
				}

				auto res = m_expression->Execute();
				m_stack->Close();
				return res;
			}

			// Empty return
			return ObjectGenerator::GenerateNone();
		}

	private:
		unique_ptr<ActionNode> m_expression;
		shared_ptr<Stack> m_stack;
	};
}
