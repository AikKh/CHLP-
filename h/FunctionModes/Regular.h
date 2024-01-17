#pragma once

#include "../Mode.h"

class Regular : public ModeData {
public:

	Regular(CompoundNode* argsNode = nullptr) : ModeData(Mode::REGULAR, argsNode) {}

	Node* GetValue() const override {
		if (!HasValue()) {
			throw std::logic_error("This regular function doesn't have arguments");
		}
		return ModeData::GetValue();
	}
};