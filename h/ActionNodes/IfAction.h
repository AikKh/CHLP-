#pragma once

#include "../ActionNode.h"
#include "CompoundAction.h"

namespace Doer
{

	class IfAction : public ActionNode {
	public:
		IfAction(vector <unique_ptr< ActionNode >> conditions, vector <unique_ptr< ActionNode >> bodies, unique_ptr<ActionNode> else_body, StackFrame*& stack) :
			m_conditions{ std::move(conditions) }, m_bodies{ std::move(bodies) }, m_else{ std::move(else_body) }, m_stack{ stack }
		{
			if (m_conditions.size() != m_bodies.size())
			{
				throw std::logic_error("m_conditions.size() != m_bodies.size()");
			}
		}

		shared_ptr<Object> Execute() const override
		{
			for (int i = 0; i < m_conditions.size(); i++)
			{
				auto cond = m_conditions[i]->Execute();
				
				if (!cond)
				{
					error.Report("Failed to evaluate if statement condition", ErrorPriority::RUNTIME_ERROR);
					return nullptr;
				}

				auto eval = cond->CallMethod(MethodType::BOOL, {});
				auto value = reinterpret_cast<const bool*>(cond->GetPtr());

				if (*value)
				{
					const CompoundAction* comp_action = dynamic_cast<const CompoundAction*>(m_bodies[i].get());
					if (comp_action == nullptr)
					{
						throw std::logic_error("If statement body should be CompoundAction");
					}
					return comp_action->ExecuteWithReturn(m_stack);
				}
			}

			if (m_else)
			{
				const CompoundAction* comp_action = dynamic_cast<const CompoundAction*>(m_else.get());
				if (comp_action == nullptr)
				{
					throw std::logic_error("Else statement body should be CompoundAction");
				}
				return comp_action->ExecuteWithReturn(m_stack);
			}

			return nullptr;
		}

	private:
		vector <unique_ptr< ActionNode >> m_conditions;
		vector <unique_ptr< ActionNode >> m_bodies;
		unique_ptr<ActionNode> m_else;

		StackFrame*& m_stack;
	};
}
