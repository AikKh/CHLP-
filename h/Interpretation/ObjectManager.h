#pragma once

#include <unordered_map>
#include <type_traits>

#include "../MemoryManagement/Type.h"
#include "../MemoryManagement/Object.h"

namespace Doer
{
	class ObjectGenerator;

	struct TupleHash {
		template <class T1, class T2, class T3>
		std::size_t operator()(const std::tuple<T1, T2, T3>& t) const
		{
			auto h1 = std::hash<T1>{}(std::get<0>(t));
			auto h2 = std::hash<T2>{}(std::get<1>(t));
			auto h3 = std::hash<T3>{}(std::get<2>(t));
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
	
	class ObjectManager {
	public:
		using OperationFunction = Object::ObjectPtr(*)(Object::ObjectPtr, Object::ObjectPtr); 
		using OperationMap = std::unordered_map <std::tuple< Type, Type, MethodType >, OperationFunction, TupleHash>;

		static OperationFunction Lookup(Type t1, Type t2, MethodType mt);

	private:
		static unique_ptr<OperationMap> InitializeMap();

	private:
		template<typename T1, typename T2, typename T3, MethodType method>
		static Doer::Object::ObjectPtr Operation(Doer::Object::ObjectPtr, Doer::Object::ObjectPtr);
	};
}
