#pragma once

#include "../Node.h"

namespace Doer {

	class IfNode : public Node {
	public:
		IfNode(vector<Node*> conditions, vector<Node*> bodies, Node* else_body = nullptr) : 
			m_conditions{ conditions }, m_bodies{ bodies }, m_else_body{ else_body } {}

		~IfNode() override
		{
			for (Node* cond : m_conditions) delete cond;
			for (Node* body : m_bodies) delete body;

			if (m_else_body) {
				delete m_else_body;
			}
		}

		const vector<Node*>& GetConditions() const
		{
			return m_conditions;
		}

		const vector<Node*>& GetBodies() const
		{
			return m_bodies;
		}

		const Node* GetElseBody() const
		{
			return m_else_body;
		}

		void Print(int level = 0) const override
		{
			string ind = string(level, ' ');

			cout << ind << "If statement: " << endl;

			cout << ind << "Condition: " << endl;
			m_conditions[0]->Print(level + Indedention);

			cout << ind << "Body: " << endl;
			m_bodies[0]->Print(level + Indedention);

			for (int i = 1; i < m_conditions.size(); i++)
			{
				cout << ind << "Elif statement: " << endl;

				cout << ind << "Condition: " << endl;
				m_conditions[i]->Print(level + Indedention);

				cout << ind << "Body: " << endl;
				m_bodies[i]->Print(level + Indedention);
			}

			if (m_else_body)
			{
				cout << ind << "Else statement: " << endl;

				cout << ind << "Body: " << endl;
				m_else_body->Print(level + Indedention);
			}
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

	private:
		vector<Node*> m_conditions;
		vector<Node*> m_bodies;
		Node* m_else_body;
	};
}