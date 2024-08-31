#pragma once

#include "../Node.h"

namespace Doer {

	class LeafNode : public Node {
	public:
		LeafNode(Token value) : _value{ move(value) } {}

		~LeafNode() override = default;

		const Token& GetValue() const& { return _value; }

		Token GetValue() && { return std::move(_value); }

		void Print(int level = 0) const override {
			cout << string(level, ' ') << _value.GetText() << endl;
		}

		ActionNode* Accept(ActionTreeGenerator&) const override;

	private:
		Token _value;
	};
}