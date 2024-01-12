#pragma once

#include "Operator.h"

class AllOperators {
public:

	const int MaxPrecedence = 8;

	bool FindOperatorByText(string text, Operator& oper, Operator::InputTaken input) {
		for (auto& op : PrecedenceMap) {
			if (op.GetText() == text && op.GetInputTaken() == input) {
				oper = op;
				return true;
			}
		}
		return false;
	}

private:

	vector<Operator> PrecedenceMap = {
			Operator("or",  8,	Operator::BOTH),

			Operator("and", 7,	Operator::BOTH),
													  
			Operator("==",  6,	Operator::BOTH),
			Operator("!=",  6,	Operator::BOTH),
										
			Operator("<",   5,	Operator::BOTH),
			Operator("<=",  5,	Operator::BOTH),
			Operator(">",   5,	Operator::BOTH),
			Operator(">=",  5,	Operator::BOTH),
										
			Operator("<",   4,	Operator::BOTH),
			Operator("<=",  4,	Operator::BOTH),
										
			Operator("+",   3,	Operator::BOTH),
			Operator("-",   3,	Operator::BOTH),
										
			Operator("*",   2,	Operator::BOTH),
			Operator("/",   2,	Operator::BOTH),

			Operator("^",   1,	Operator::BOTH),

			Operator("not", 1,	Operator::RIGHT),
			Operator("+",   1,	Operator::RIGHT),
			Operator("-",   1,	Operator::RIGHT),
	};
};

extern AllOperators operators;