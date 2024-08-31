#pragma once

#include "Object.h"

namespace Doer
{
	// Create a separete class for creating having objects like true, false, none
	//static const Object::ObjectPtr None;
	class FunctionCore;
	class StackFrame;

	class ObjectGenerator {
	public:
		static Object::ObjectPtr GenerateInt(int value);

		static Object::ObjectPtr GenerateFloat(float value);

		static Object::ObjectPtr GenerateBool(bool value);

		static const Object::ObjectPtr GenerateNone();

		static Object::ObjectPtr GenerateFunction(FunctionCore func, StackFrame*& stack);

	private:
		static bool AssertArgumentCount(Type type, std::size_t right_arg_count, std::size_t arg_count);

		static Object::ObjectPtr CallMethod(Object::ObjectPtr obj, vector<Object::ObjectPtr> args, MethodType method_type);
	};

}
