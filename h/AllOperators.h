#pragma once

#include "Operator.h"

class AllOperators {
public:

	bool FindOperatorByText(string text, Operator& oper, Operator::InputTaken input) {
		for (auto& op : PrecedenceMap) {
			if (op.GetText() == text && op.GetInputTaken() == input) {
				oper = op;
				return true;
			}
		}
		return false;
	}

	bool IsOperator(string text) {
		for (auto& op : PrecedenceMap) {
			if (op.GetText() == text) {
				return true;
			}
		}
		return false;
	}

private:

	vector<Operator> PrecedenceMap = {
		Operator("=",   10,	Operator::BOTH, Operator::Associativity::RIGHT),

		Operator("or",  9,	Operator::BOTH),

		Operator("and", 8,	Operator::BOTH),
													  
		Operator("==",  7,	Operator::BOTH),
		Operator("!=",  7,	Operator::BOTH),
										
		Operator("<",   6,	Operator::BOTH),
		Operator("<=",  6,	Operator::BOTH),
		Operator(">",   6,	Operator::BOTH),
		Operator(">=",  6,	Operator::BOTH),
										
		Operator("<",   5,	Operator::BOTH),
		Operator("<=",  5,	Operator::BOTH),
										
		Operator("+",   4,	Operator::BOTH),
		Operator("-",   4,	Operator::BOTH),
										
		Operator("*",   3,	Operator::BOTH),
		Operator("/",   3,	Operator::BOTH),

		Operator("^",   2,	Operator::BOTH, Operator::Associativity::RIGHT),

		Operator("not", 1,	Operator::RIGHT),
		Operator("+",   1,	Operator::RIGHT),
		Operator("-",   1,	Operator::RIGHT),
	};
};

extern AllOperators operators;