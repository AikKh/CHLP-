#pragma once

#include "../h/MemoryManagement/Type.h"

namespace Doer {

	const Type Type::Int(TypeId::INT, INT_SIZE);
	const Type Type::Float(TypeId::FLOAT, FLOAT_SIZE);
	const Type Type::Void(TypeId::VOID, 0);
}