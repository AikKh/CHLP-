#pragma once

#include "../ActionNode.h"
//#include "../Interpretation/ObjectManager.h"

namespace Doer {

	class OperationAction : public ActionNode {
	public:
		// Takes: stack, name of var, action node for the right part
		OperationAction(ActionNode* left, ActionNode* right, OperatorId operator_id) :
			_left{ left }, _right{ right }, _operator_id{ operator_id }
		{}

		Object Execute() const override {
			Object l = _left->Execute();
			Object r = _right->Execute();

			auto op = GetOperation(l.GetType(), r.GetType());
			if (op)
			{
				return op(move(l), move(r));
			}
			
			error.Report("Failed to perform: " + 
				l.GetType().ToString() + " " + operators.GetStringFromId(_operator_id) + " " + r.GetType().ToString(),
				ErrorPriority::RUNTIME_ERROR);

			return Object::None();
		}

	private:
		inline function<Object(Object, Object)> GetOperation(Type t1, Type t2) const 
		{
			// TODO: Add validation if no operation
			//return ObjectManager::GetOperation(_operator_id, t1.GetID(), t2.GetID());
			return nullptr;
		}

	private:
		unique_ptr<ActionNode> _left;
		unique_ptr<ActionNode> _right;
		OperatorId _operator_id;
	};
}
