#include "../h/MemoryManagement/ObjectGenerator.h"

#include "../h/MemoryManagement/Object.h"
#include "../h/ActionNodes/FunctionAction.h"
//#include "../h/ActionNodes/CompoundAction.h" // Need for the function call method
#include "../h/Interpretation/ObjectManager.h"

namespace Doer
{

Object::ObjectPtr ObjectGenerator::GenerateInt(int value)
{
	auto obj = std::make_shared<Object>(Type::INT, new int{ value });

#define ADD_METHOD(type) obj->AddMethod(MethodType::type, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) { return CallMethod(obj, args, MethodType::type); });

	ADD_METHOD(ADD);
	ADD_METHOD(SUB);
	ADD_METHOD(MUL);
	ADD_METHOD(DIV);
	ADD_METHOD(MOD);

	ADD_METHOD(EQUAL);
	ADD_METHOD(NOT_EQUAL);
	ADD_METHOD(GREATER_EQUAL);
	ADD_METHOD(GREATER_THEN);
	ADD_METHOD(LESS_EQUAL);
	ADD_METHOD(LESS_THEN);

	ADD_METHOD(OR);
	ADD_METHOD(AND);

#undef ADD_METHOD

	obj->AddMethod(MethodType::BOOL, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 0, args.size()))
				return nullptr;

			const bool* value = static_cast<const bool*>(obj->GetPtr());
			return GenerateBool(value?(*value != 0):0);
		});

	return obj;

}

Object::ObjectPtr ObjectGenerator::GenerateFloat(float value)
{
	auto obj = std::make_shared<Object>(Type::FLOAT, new float{ value });

#define ADD_METHOD(type) obj->AddMethod(MethodType::type, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) { return CallMethod(obj, args, MethodType::type); });

	ADD_METHOD(ADD);
	ADD_METHOD(SUB);
	ADD_METHOD(MUL);
	ADD_METHOD(DIV);
	ADD_METHOD(MOD);

	ADD_METHOD(EQUAL);
	ADD_METHOD(NOT_EQUAL);
	ADD_METHOD(GREATER_EQUAL);
	ADD_METHOD(GREATER_THEN);
	ADD_METHOD(LESS_EQUAL);
	ADD_METHOD(LESS_THEN);

	ADD_METHOD(OR);
	ADD_METHOD(AND);

#undef ADD_METHOD

	obj->AddMethod(MethodType::BOOL, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 0, args.size()))
				return nullptr;

			const bool* value = static_cast<const bool*>(obj->GetPtr());
			return GenerateBool(value?(*value != 0):0);
		});

	return obj;
}

Object::ObjectPtr ObjectGenerator::GenerateBool(bool value)
{
	auto obj = std::make_shared<Object>(Type::BOOL, new bool{ value });

#define ADD_METHOD(type) obj->AddMethod(MethodType::type, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) { return CallMethod(obj, args, MethodType::type); });

	ADD_METHOD(OR);
	ADD_METHOD(AND);

#undef ADD_METHOD

	obj->AddMethod(MethodType::BOOL, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 0, args.size()))
				return nullptr;

			const bool* value = static_cast<const bool*>(obj->GetPtr());
			return GenerateBool(value?(*value != 0):0);
		});

	return obj;
}

const Object::ObjectPtr ObjectGenerator::GenerateNone()
{
	auto obj = std::make_shared<Object>(Type::NONE, nullptr);

	obj->AddMethod(MethodType::BOOL, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 0, args.size()))
				return nullptr;

			return GenerateBool(false);
		});

	obj->AddMethod(MethodType::AND, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 1, args.size()))
				return nullptr;

			return GenerateBool(false);
		});

	obj->AddMethod(MethodType::AND, [](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			if (!AssertArgumentCount(Type::BOOL, 1, args.size()))
				return nullptr;

			return args[0]->CallMethod(MethodType::BOOL, {});
		});

	return obj;
}

Object::ObjectPtr ObjectGenerator::GenerateFunction(FunctionCore func, shared_ptr<Stack> stack)
{
	auto obj = std::make_shared<Object>(Type::FUNCTION, new FunctionCore{ std::move(func) });

	obj->AddMethod(MethodType::CALL, [st = std::weak_ptr(stack)](Object::ObjectPtr obj, vector<Object::ObjectPtr> args) -> Object::ObjectPtr
		{
			auto stack = st.lock();
			const FunctionCore* core = static_cast<const FunctionCore*>(obj->GetPtr());

			if (!AssertArgumentCount(Type::FUNCTION, core->GetArguments().size(), args.size()))
			{
				return nullptr;
			}

			for (int i = 0; i < args.size(); i++)
			{
				auto& name = core->GetArguments()[i];
				auto& value = args[i];

				stack->Set(name, value);
			}

			return core->GetBody()->ExecuteWithReturn(stack);
		});

	return obj;
}

bool ObjectGenerator::AssertArgumentCount(Type type, std::size_t right_arg_count, std::size_t arg_count) 
{
	if (right_arg_count != arg_count)
	{
		error.Report(TypeToString(type) + " takes " + std::to_string(right_arg_count) + " argument, given " + std::to_string(arg_count),
			ErrorPriority::RUNTIME_ERROR);
		return false;
	}

	return true;
}

Object::ObjectPtr ObjectGenerator::CallMethod(Object::ObjectPtr obj, vector<Object::ObjectPtr> args, MethodType method_type)
{
	if (!AssertArgumentCount(obj->GetType(), 1, args.size()))
		return nullptr;

	auto func = ObjectManager::Lookup(obj->GetType(), args[0]->GetType(), method_type);
	if (func)
	{
		return func(obj, args[0]);
	}

	return nullptr;
};

}
