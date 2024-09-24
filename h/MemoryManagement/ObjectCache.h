#pragma once

#include "Object.h"

namespace Doer
{
	class ObjectCache {
	public:
		std::map<int, shared_ptr<Object>> Numbers;

		shared_ptr<Object> True = nullptr;
		shared_ptr<Object> False = nullptr;
	};
}
