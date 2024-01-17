#pragma once

#include "../Mode.h"

class Conditional : public ModeData {
public:

	Conditional(Node* conditionExpression) : ModeData(Mode::CONDITIONAL, conditionExpression) {
		if (conditionExpression == nullptr) {
			error.Report("Conditional function should have a condition!", ErrorPriority::SOURCE_ERROR);
			//throw std::logic_error("Conditional mode should have a condition!");
		}
	}
};