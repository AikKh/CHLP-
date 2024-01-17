#pragma once

#include "../Node.h"

class NullNode : public Node {
public:
	~NullNode() = default;

	void Print(int level = 0) const override {
		cout << string(level, ' ') << "NULL" << endl;
	}
};