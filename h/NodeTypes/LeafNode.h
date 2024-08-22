#pragma once

#include "../Node.h"

namespace Doer {

	class HasValue {
	public:
		virtual const Token& GetValue() const = 0;
	};

	class LeafNode : public Node, public HasValue {
	public:
		LeafNode(Token value) : _value{ move(value) } {}

		~LeafNode() override = default;

		const Token& GetValue() const { return _value; }

		ActionNode* Accept(Visitor& runner) const override;

		void Print(int level = 0) const override {
			cout << string(level, ' ') << _value.GetText() << endl;
		}

	private:
		Token _value;
	};
}