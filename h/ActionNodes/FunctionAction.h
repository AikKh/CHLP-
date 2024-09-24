#pragma once

#include "../ActionNode.h"
#include "CompoundAction.h"
#include "../MemoryManagement/StackFrame.h"
#include "../MemoryManagement/ObjectGenerator.h"

namespace Doer 
{
	class FunctionCore {
	public:
		FunctionCore(vector<string> args, CompoundAction* body) : m_arguments{ std::move(args) }, m_body{ body } {}

		const vector<string>& GetArguments() const { return m_arguments; }

		const CompoundAction* GetBody() const { return m_body; }

	private:
		vector<string> m_arguments;
		CompoundAction* m_body;
	};

	class FunctionAction : public ActionNode {
	public:
		FunctionAction(shared_ptr<Stack> stack, const string& id, vector<string> args, unique_ptr<ActionNode> body) :
			m_stack{ std::move(stack) }, m_id{ id }, m_args{ std::move(args) }, m_body{ std::move(body) }
		{} 

		shared_ptr<Object> Execute() const override
		{
			CompoundAction* body = dynamic_cast<CompoundAction*>(m_body.get());

			if (body == nullptr)
			{
				throw std::logic_error("Function body should be compound node");
			}

			FunctionCore func{ std::move(m_args), body };
			m_stack->Set(m_id, ObjectGenerator::GenerateFunction(std::move(func), m_stack));

			return nullptr;
		}

	private:
		shared_ptr<Stack> m_stack;
		const string& m_id;
		vector<string> m_args;
		unique_ptr<ActionNode> m_body;
	};
}
