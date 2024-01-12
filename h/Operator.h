#pragma once

#include "includes.h"

class Operator {

public:

	Operator() {}

	enum InputTaken
	{
		LEFT,
		RIGHT,
		BOTH
	};

	const string& GetText() const {
		return _text;
	}

	int GetPrecedence() const {
		return _precedence;
	}

	InputTaken GetInputTaken() const {
		return _input;
	}

	/*bool TakesLeftInput() { 
		return _input == BOTH || _input == LEFT;
	}

	bool TakesRightInput() { 
		return _input == BOTH || _input == RIGHT;
	}*/

private:

	Operator(string text, int precedence, InputTaken input) : _text(text), _input(input), _precedence(precedence) {}

	string _text;

	InputTaken _input;

	int _precedence;

	friend class AllOperators;
};