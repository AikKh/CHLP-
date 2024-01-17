#pragma once

#include "../Mode.h"

class Immediate : public ModeData {
public:

	Immediate() : ModeData(Mode::IMMEDIATE) {}

	Node* GetValue() const override{
		throw std::logic_error("Immediate mode can't have a value!");
	}
};