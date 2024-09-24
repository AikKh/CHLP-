#pragma once

#include <map>

#include "Type.h"
#include "../ErrorHandler.h"

namespace Doer
{
	class Object final : public std::enable_shared_from_this<Object> {
	public:
		using ObjectPtr = shared_ptr<Object>;
		using Method = function<ObjectPtr(ObjectPtr, vector<ObjectPtr> args)>;

		Object() : m_type{ Type::NONE }, m_data{ nullptr } {}

		Object(Type type, void* data) : m_type{ type }, m_data{ data } {}

		Type GetType() const
		{
			return m_type;
		}

		const void* GetPtr() const
		{
			return m_data;
		}

		void AddMethod(MethodType type, Method method)
		{
			m_methods.insert({ type, std::move(method) });
		}

		ObjectPtr CallMethod(MethodType method, vector<ObjectPtr> args)
		{
			if (m_methods.find(method) == m_methods.end())
			{
				return nullptr;
			}
			auto& m = m_methods.at(method);
			return m(shared_from_this(), std::move(args));
		}

		~Object()
		{
			delete m_data;
		}

	private:
		Type m_type;
		std::map<MethodType, Method> m_methods;
		void* m_data;
	};
}