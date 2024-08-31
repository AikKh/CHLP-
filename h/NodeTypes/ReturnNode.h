#pragma once

#include "../Node.h"

namespace Doer
{

	class ReturnNode : public Node {
	public:
		ReturnNode(Node* expr) : m_expr{ expr } {}

		~ReturnNode() override
		{
			delete m_expr;
		}

		const Node* GetExpression() const
		{
			return m_expr;
		}

		void Print(int level = 0) const override
		{
			string ind = string(level, ' ');

			cout << ind << "Return: " << endl;
			m_expr->Print(level + Indedention);
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

	private:
		Node* m_expr;
	};
}