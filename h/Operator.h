#pragma once

#include "Includes.h"
#include "Token.h"

namespace Doer {

	class Operator {
	public:
		Operator() = default;

		enum InputTaken
		{
			LEFT,
			RIGHT,
			BOTH
		};

		enum class Associativity {
			LEFT,
			RIGHT,
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

		Associativity GetAssociativity() const {
			return _assoc;
		}

		/*bool TakesLeftInput() {
			return _input == BOTH || _input == LEFT;
		}

		bool TakesRightInput() {
			return _input == BOTH || _input == RIGHT;
		}*/

	private:

		Operator(string text, int precedence, InputTaken input, Associativity assoc = Associativity::LEFT)
			: _text(text), _input(input), _precedence(precedence), _assoc(assoc) {}

		string _text;

		InputTaken _input;

		Associativity _assoc;

		int _precedence;

		friend class AllOperators;
	};
}