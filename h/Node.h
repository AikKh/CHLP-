#pragma once

#include "../h/ActionNode.h"
#include "ErrorHandler.h"

namespace Doer {

	class Value;
	class Visitor;

	class Node {
	public:
		virtual ActionNode* Accept(Visitor& runner) const = 0;

		virtual void Print(int level = 0) const = 0;

		virtual ~Node() = default;

	protected:
		// For printing
		static const int Indedention = 3;
	};
}