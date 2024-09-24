#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/StackFrame.h"

namespace Doer {

	class AccessAction : public ActionNode {
	public:
		AccessAction(shared_ptr<Stack> stack, const string& id) :
			m_stack{ std::move(stack) }, m_id{ id }
		{}

		shared_ptr<Object> Execute() const override
		{
			auto res = m_stack->Get(m_id);

			if (!res)
			{
				error.Report("Unknown variable " + m_id, ErrorPriority::RUNTIME_ERROR);
			}
			return res;
		}

	private:
		const shared_ptr<Stack> m_stack;
		const string& m_id;
	};
}
