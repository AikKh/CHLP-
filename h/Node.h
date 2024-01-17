#pragma once

#include "Token.h"
#include "ErrorHandler.h"

class Node {
public:
	virtual void Print(int level = 0) const = 0;

protected:
	// For printing
	static const int Indedention = 3;
};