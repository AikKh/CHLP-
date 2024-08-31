#pragma once

#include "../Includes.h"

#define STR(value) #value

namespace Doer {

	enum class Type {
		INT, 
		FLOAT,
		BOOL,
		FUNCTION,
		NONE
	};

	enum class MethodType {
		// Operations
		ADD,
		SUB,
		MUL,
		DIV,
		MOD,

		// Comparison
		LESS_THEN,
		LESS_EQUAL,
		EQUAL,
		NOT_EQUAL,
		GREATER_EQUAL,
		GREATER_THEN,

		OR,
		AND,

		// Casts
		INT, 
		FLOAT,
		BOOL,

		CALL,
		SIZE,
		NEW,

		REPR
	};

	inline string TypeToString(Type type)
	{
		switch (type)
		{
		case Doer::Type::INT:
			return "Integer";
		case Doer::Type::FLOAT:
			return "Float";
		case Doer::Type::BOOL:
			return "Bool";
		case Doer::Type::FUNCTION:
			return "Function";
		case Doer::Type::NONE:
			return "None";
		default:
			throw std::logic_error("Got unknown type while converting type to string");
		}
	}

	inline string TypeToString(MethodType type)
	{
		switch (type)
		{
		case Doer::MethodType::ADD:
			return "+";
		case Doer::MethodType::SUB:
			return "-";
		case Doer::MethodType::MUL:
			return "*";
		case Doer::MethodType::DIV:
			return "/";
		case Doer::MethodType::MOD:
			return "%";

		case Doer::MethodType::INT:
			return "int cast";
		case Doer::MethodType::FLOAT:
			return "float cast";
		case Doer::MethodType::BOOL:
			return "bool cast";

		case Doer::MethodType::GREATER_EQUAL:
			return ">=";
		case Doer::MethodType::GREATER_THEN:
			return ">";
		case Doer::MethodType::LESS_EQUAL:
			return "<=";
		case Doer::MethodType::LESS_THEN:
			return "<";
		case Doer::MethodType::EQUAL:
			return "==";
		case Doer::MethodType::NOT_EQUAL:
			return "!=";

		case Doer::MethodType::OR:
			return "or";
		case Doer::MethodType::AND:
			return "and";

		case Doer::MethodType::CALL:
			return "call";
		case Doer::MethodType::SIZE:
			return "size of";
		case Doer::MethodType::NEW:
			return "new";
		default:
			break;
		}
	}
}