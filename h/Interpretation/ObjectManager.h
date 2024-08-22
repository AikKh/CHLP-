//#pragma once
//
//#include "../MemoryManagement/Object.h"
//#include "../AllOperators.h"
//
//// Contains operation logics between objects, run time validation of operations.
//// 
//// The main function here will be called GetOperation
//// Prototype:
//// function<Object(Object, Object)> GetOperation(OperatorId op_id, TypeId type1, TypeId type2);
//// 
//// Based on type1, type2 and op_id, validation will be performed first, and then if validation is passed
//// the operation function will be returned
//// 
//// Validation:
//// It will use various tables (I don't know how yet). Also as a result of validation the return type of object will
//// be deduced. Tables should contain info about "can be a cretain operator used for certain types". Failed validation
//// will result it type mismatch error at runtime
//
//namespace Doer {
//
//	class ObjectManager {
//	public:
//		using Operation = function<Object(const Object&, const Object&)>;
//
//		static void CanonicalizeObjects(Object& a, Object& b)
//		{
//			if (a.GetType().GetID() > b.GetType().GetID())
//			{
//				std::swap(a, b);
//			}
//		}
//		
//		static Operation GetOperation(OperatorId op, TypeId t1, TypeId t2)
//		{
//			auto key = make_tuple(op, t1, t2);
//			if (operations.find(key) != operations.end())
//			{
//				return operations[key];
//			}
//			return nullptr;
//		}
//
//		static void InitializeOperations()
//		{
//#define REG(OpId, Op) RegisterOperation(OperatorId::OpId, TypeId::INT, TypeId::INT, [](const Object& lhs, const Object& rhs ) \
//			{ \
//				return Object::Link(Type::Get(TypeId::INT), new int{ lhs.ToInt() Op rhs.ToInt() });\
//			});
//
//			REG(Add, +);
//			REG(Sub, -);
//			REG(Mul, *);
//			REG(Div, -);
//			REG(Mod, %);
//
//#undef REG
//		}
//
//	private:
//		static void RegisterOperation(OperatorId op, TypeId t1, TypeId t2, Operation operation)
//		{
//			operations[std::make_tuple(op, t1, t2)] = operation;
//		}
//
//	private:
//		static inline unordered_map<tuple<OperatorId, TypeId, TypeId>, Operation> operations;
//	};
//}
//
