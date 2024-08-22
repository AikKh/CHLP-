#pragma once

#include "Type.h"
#include "../ErrorHandler.h"

namespace Doer {

	class ObjectManager;

	class Object final {
	public:
		//Object(int number) : _type(Type::Get(TypeID::INT)), _ptr(malloc(_type.GetSize())) { // Need to optimize this
		//	if (_ptr != nullptr) {
		//		*((int*)_ptr) = number;
		//		return;
		//	}
		//	throw std::bad_alloc();
		//}
		//Object(const Object& other) : _type{ other._type } {
		//	_ptr = malloc(_type.GetSize());
		//	if (_ptr == nullptr || _type == Type::Get(TypeID::VOID)) {
		//		throw std::bad_alloc();
		//	}
		//	memcpy(_ptr, other._ptr, _type.GetSize());
		//}
		//Object(size_t size, void* source) { // take type instead of size
		//	_ptr = nullptr;
		//	if (size) {
		//		_ptr = malloc(size);
		//		if (_ptr) {
		//			std::memcpy(_ptr, source, size);
		//		}
		//	}
		//}

		Object(Object&& other) noexcept : _type{ other._type }
		{
			_ptr = other._ptr;
			other._ptr = nullptr;
		}

		~Object() {
			delete _ptr;
		}

		Type GetType() const&
		{
			return _type;
		}

		void* GetPtr() const 
		{
			return _ptr;
		}

		Object& operator=(Object&& other) noexcept 
		{
			if (this != &other) {
				delete _ptr;

				_type = other._type;
				_ptr = other._ptr;

				other._type = Type::Get(TypeId::VOID);
				other._ptr = nullptr;
			}

			return *this;
		}

	// Conversions
	public:
		int ToInt() const
		{
			if (GetType() != Type::Get(TypeId::INT)) return HandleTypeMismatch<int>(Type::Get(TypeId::INT));
			return *(static_cast<int*>(_ptr));
		}

		float ToFloat() const
		{
			if (GetType() != Type::Get(TypeId::INT)) return HandleTypeMismatch<float>(Type::Get(TypeId::FLOAT));
			return *(static_cast<float*>(_ptr));
		}

		// Add more convertions with more types

	public:
		static Object New(Type type)
		{
			return Object(type);
		}

		static Object Copy(Type type, const void* source)
		{
			auto ptr = malloc(type.GetSize());

			if (ptr == nullptr)
			{
				throw std::bad_alloc();
			}
			memcpy(ptr, source, type.GetSize());
			return Object(type, ptr);
		}

		static Object Copy(const Object& other)
		{
			return Copy(other._type, other._ptr);
		}

		static Object Link(Type type, void* source) 
		{
			return Object(type, source);
		}

		static Object Link(const Object& other)
		{
			return Object(other._type, other._ptr);
		}

		static Object None()
		{
			return Object(Type::Get(TypeId::VOID));
		}

	private:
		Object(Type type) : _type{ type } 
		{
			if (_type.GetSize() > 0) 
			{
				_ptr = malloc(_type.GetSize());
				if (_ptr == nullptr) throw std::bad_alloc();
			}
		}

		Object(Type type, void* ptr) : _type{ type }, _ptr{ ptr } {}

		/*Object(const Object& other) : _type{ other._type } 
		{
			auto ptr = malloc(other._type.GetSize());
			if (ptr == nullptr) throw std::bad_alloc();

			memcpy(ptr, other._ptr, other._type.GetSize());
			_ptr = ptr;
		}*/

		template<typename T>
		T HandleTypeMismatch(Type type) const
		{
		  	error.Report("Can't convert " + GetType().ToString() + " to " + type.ToString(), 
				ErrorPriority::RUNTIME_ERROR);

			return T();
		}

	private:
		Type _type;
		void* _ptr = nullptr;

		friend class ObjectManager;
	};

	const Object None = Object::New(Type::Get(TypeId::VOID));
}
