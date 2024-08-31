#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/ObjectGenerator.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer
{
	class ReturnAction : public ActionNode {
	public:
		ReturnAction(ActionNode* expression, StackFrame*& stack) : m_expression{ expression }, m_stack{ stack } {}

		shared_ptr<Object> Execute() const override
		{
			if (m_expression)
			{
				if (m_stack->GetPrevious() == nullptr)
				{
					error.Report("Cannot return in global namespace", ErrorPriority::RUNTIME_ERROR);
					return nullptr;
				}

				auto res = m_expression->Execute();
				m_stack = StackFrame::Close(m_stack);
				return res;
			}

			// Empty return
			return ObjectGenerator::GenerateNone();
		}

	private:
		unique_ptr<ActionNode> m_expression;
		StackFrame*& m_stack;
	};
}
