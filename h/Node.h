#pragma once

#include "Token.h"
#include "ErrorHandler.h"

class Node {
public:
	Node(Token value) : _value(value){}

	~Node() = default;

	virtual void Print(int level = 0)
	{
		cout << string(level, ' ') << _value.GetText() << endl;
	}

protected:
	Token _value;

	// For printing
	static const int Indedention = 3;
};