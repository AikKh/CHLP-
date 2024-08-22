#pragma once

#include "../ActionNode.h"

namespace Doer {

	class LiteralAction : public ActionNode {
	public:
		LiteralAction(const string& text) : _text{ text } {}

		// TODO: change logic: make it work not only for int
		Object Execute() const override {
			int num{};

			try {
				num = std::stoi(_text);
				return Object::Link(Type::Get(TypeId::INT), new int{ num });
			}
			catch (...) {
				error.Report("Invalid literal value " + _text, ErrorPriority::SOURCE_ERROR);
				return Object::None();
			}
		}

	private:
		const string& _text;
	};
}
