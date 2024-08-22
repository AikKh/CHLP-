#pragma once

#include "Node.h"

namespace Doer {

	enum Mode {
		IMMEDIATE,
		CONDITIONAL,
		REGULAR
	};

	class ModeData {
	public:
		ModeData() = default;

		bool HasValue() const {
			return _hasValue;
		}

		virtual Node* GetValue() const {
			return _value;
		}

		Mode GetMode() const {
			return _mode;
		}

	protected:

		ModeData(Mode mode, Node* value = nullptr) : _hasValue(value != nullptr), _mode(mode), _value(value) {}

		Mode _mode;

	private:

		bool _hasValue;
		Node* _value;
	};
}