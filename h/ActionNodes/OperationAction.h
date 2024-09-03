#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/ObjectGenerator.h"

namespace Doer 
{
	class OperationAction : public ActionNode {
	public:
		// Takes: stack, name of var, action node for the right part
		OperationAction(ActionNode* left, ActionNode* right, OperatorId operator_id) :
			_left{ left }, _right{ right }, _operator_id{ operator_id }
		{}

		shared_ptr<Object> Execute() const override {
			auto l = _left->Execute();
			auto r = _right->Execute();

			if (!l || !r)
			{
				error.Report("Got error while performing operation", ErrorPriority::RUNTIME_ERROR);
				return nullptr;
			}

			MethodType method = ConvertOperatorIdToMethod();

			return TryToCallMethod(method, l, r);
		}

	private:
		Object::ObjectPtr TryToCallMethod(MethodType method, Object::ObjectPtr& left, Object::ObjectPtr& right) const
		{
			Object::ObjectPtr res;

			res = left->CallMethod(method, { right });

			if (res)
				return res;

			error.Report(
				TypeToString(left->GetType()) + " " + TypeToString(method) + " " + TypeToString(right->GetType()) + " is undefined",
				ErrorPriority::RUNTIME_ERROR);
			return nullptr;
		}

		MethodType ConvertOperatorIdToMethod() const
		{
			switch (_operator_id)
			{
			case Doer::OperatorId::Add:
				return MethodType::ADD;

			case Doer::OperatorId::Sub:
				return MethodType::SUB;
			
			case Doer::OperatorId::Mul:
				return MethodType::MUL;
			
			case Doer::OperatorId::Div:
				return MethodType::DIV;
			
			case Doer::OperatorId::Less:
				return MethodType::LESS_THEN;
			
			case Doer::OperatorId::LessOrEqual:
				return MethodType::LESS_EQUAL;
			
			case Doer::OperatorId::Greater:
				return MethodType::GREATER_THEN;
			
			case Doer::OperatorId::GreaterOrEqual:
				return MethodType::GREATER_EQUAL;
			
			case Doer::OperatorId::Equals:
				return MethodType::EQUAL;
			
			case Doer::OperatorId::NotEquals:
				return MethodType::NOT_EQUAL;
			
			case Doer::OperatorId::And:
				return MethodType::AND;
			
			case Doer::OperatorId::Or:
				return MethodType::OR;

			default:
				throw std::logic_error("OperationAction failed to find suitable action");
			}
		}

	private:
		unique_ptr<ActionNode> _left;
		unique_ptr<ActionNode> _right;
		OperatorId _operator_id;
	};
}
