#pragma once

#include "../h/Interpretation/ActionTreeGenerator.h"
#include "ErrorHandler.h"

namespace Doer {

	class Node {
	public:
		virtual ActionNode* Accept(ActionTreeGenerator& runner) const = 0;

		virtual void Print(int level = 0) const = 0;

		virtual ~Node() = default;

	protected:
		// For printing
		static const int Indedention = 3;
	};
}