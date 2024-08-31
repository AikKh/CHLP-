#pragma once

#include "Operator.h"

namespace Doer {

	enum class OperatorId
	{
		Assign,

		AddAssign,
		SubAssign,
		MulAssign,
		DivAssign,
		ModAssign,
		ExpAssign,

		Or,

		And,

		Equals,
		NotEquals,

		Less,
		LessOrEqual,
		Greater,
		GreaterOrEqual,

		Add,
		Sub,

		Mul,
		Div,
		Mod,

		Exp,

		Not,
		Plus,
		Minus
	};

	class AllOperators {
	public:
		bool SearchOperatorId(const string& text, OperatorId& id)
		{
			for (auto& [key, value] : PrecedenceMap)
			{
				if (value.GetText() == text)
				{
					id = key;
					return true;
				}
			}

			return false;
		}

		bool SearchOperator(const string& text, Operator& oper, Operator::InputTaken input)
		{
			for (auto& [_, value] : PrecedenceMap) 
			{
				if (value.GetText() == text && value.GetInputTaken() == input) 
				{
					oper = value;
					return true;
				}
			}
			return false;
		}

		bool IsOperator(const string& text) {
			for (auto& [_, value] : PrecedenceMap)
			{
				if (value.GetText() == text) 
				{
					return true;
				}
			}
			return false;
		}

		const string& GetStringFromId(OperatorId id)
		{
			return PrecedenceMap.at(id).GetText();
		}

	private:

		unordered_map<OperatorId, Operator> PrecedenceMap = {

			{ OperatorId::Assign,         Operator("=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },

			{ OperatorId::AddAssign,	  Operator("+=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },
			{ OperatorId::SubAssign,	  Operator("-=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },
			{ OperatorId::MulAssign,	  Operator("*=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },
			{ OperatorId::DivAssign,	  Operator("/=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },
			{ OperatorId::ModAssign,	  Operator("%=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },
			{ OperatorId::ExpAssign,	  Operator("^=",   10,	Operator::BOTH, Operator::Associativity::RIGHT) },

			{ OperatorId::Or,			  Operator("or",  9,	Operator::BOTH) },

			{ OperatorId::And,			  Operator("and", 8,	Operator::BOTH) },

			{ OperatorId::Equals,		  Operator("==",  7,	Operator::BOTH) },
			{ OperatorId::NotEquals,	  Operator("!=",  7,	Operator::BOTH) },

			{ OperatorId::Less,		  Operator("<",   6,	Operator::BOTH) },
			{ OperatorId::LessOrEqual, Operator("<=",  6,	Operator::BOTH) },
			{ OperatorId::Greater,		  Operator(">",   6,	Operator::BOTH) },
			{ OperatorId::GreaterOrEqual,  Operator(">=",  6,	Operator::BOTH) },

			{ OperatorId::Add,			  Operator("+",   4,	Operator::BOTH) },
			{ OperatorId::Sub,			  Operator("-",   4,	Operator::BOTH) },

			{ OperatorId::Mul,			  Operator("*",   3,	Operator::BOTH) },
			{ OperatorId::Div,			  Operator("/",   3,	Operator::BOTH) },
			{ OperatorId::Mod,			  Operator("%",   3,	Operator::BOTH) },

			{ OperatorId::Exp,			  Operator("^",   2,	Operator::BOTH, Operator::Associativity::RIGHT) },

			{ OperatorId::Not,			  Operator("not", 1,	Operator::RIGHT) },
			{ OperatorId::Plus,			  Operator("+",   1,	Operator::RIGHT) },
			{ OperatorId::Minus,		  Operator("-",   1,	Operator::RIGHT) },
		};
	};

	extern AllOperators operators;
}