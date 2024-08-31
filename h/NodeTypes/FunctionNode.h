#pragma once

#include "../Node.h"
#include "CompoundNode.h"

namespace Doer {

	class FunctionNode : public Node {
	public:

		FunctionNode(string id, CompoundNode* args, CompoundNode* body)
			: m_id(id), m_args(args), m_body(body)
		{
			if (body == nullptr) {
				error.Report("Function can't be without body", ErrorPriority::SOURCE_ERROR);
			}
		}

		~FunctionNode() override {
			delete m_args;
			delete m_body;
		}

		void Print(int level = 0) const override {
			string ind = string(level, ' ');

			cout << ind << "Function: " << m_id << endl;

			cout << ind << "Args: " << m_id << endl;
			m_args->Print(level + Indedention);

			cout << ind << "Body: " << m_id << endl;
			m_body->Print(level + Indedention);
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

		const string& GetName() const& 
		{
			return m_id;
		}

		string GetName() &&
		{
			return std::move(m_id);
		}

		CompoundNode* GetArgs() const
		{
			return m_args;
		}

		CompoundNode* GetBody() const
		{
			return m_body;
		}

	private:
		string m_id;
		CompoundNode* m_args;
		CompoundNode* m_body;
	};
}