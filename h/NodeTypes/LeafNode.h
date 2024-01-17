#pragma once

#include "../Node.h"

class LeafNode : public Node {

public:
	LeafNode(Token value) : _value(value) {}

	~LeafNode() = default;

	void Print(int level = 0) const override {
		cout << string(level, ' ') << _value.GetText() << endl;
	}

private:
	Token _value;
};