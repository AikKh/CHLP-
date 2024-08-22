#pragma once

#include "../Includes.h"

namespace Doer {

	enum class TypeId {
		INT, FLOAT, VOID
	};

	// TODO: Simplify this piece of shit
	class Type {
	public:
		inline TypeId GetID() const { return _id; }
		inline size_t GetSize() const { return _size; }

		Type() = delete;

		string ToString() const {
			switch (_id)
			{
			case Doer::TypeId::INT:
				return "Int";
			case Doer::TypeId::FLOAT:
				return "Float";
			case Doer::TypeId::VOID:
				return "Void";
			default:
				throw std::logic_error("Not implemented type id for to string");
			}
		}

		bool operator==(const Type& other) const
		{
			return _id == other._id;
		}

		bool operator!=(const Type& other) const
		{
			return _id != other._id;
		}

		static Type Get(TypeId id) {
			switch (id)
			{
			case Doer::TypeId::INT:   return Int;
			case Doer::TypeId::FLOAT: return Float;
			case Doer::TypeId::VOID:  return Void;
			default: throw std::runtime_error("Unknown type id");
			}
		}

	private:
		Type(TypeId id, size_t size) : _id(id), _size(size) { }

	private:
		TypeId _id;
		size_t _size;

		static const Type Int;
		static const Type Float;
		static const Type Void;
	};
}