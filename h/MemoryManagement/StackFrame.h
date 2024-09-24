#pragma once

#include "Object.h"
#include "../ErrorHandler.h"

namespace Doer
{
	class StackFrame {
	public:
		explicit StackFrame(StackFrame* previous) : m_previous(previous) {}

		void Set(const string& name, shared_ptr<Object> obj)
		{
			m_symbolTable[name] = std::move(obj);
		}

		shared_ptr<Object> Get(const string& name) const
		{
			if (!(InTable(name)))
			{
				if (GetPrevious() != nullptr)
				{
					return GetPrevious()->Get(name);
				}
				return nullptr;
			}
			return m_symbolTable.at(name);
		}

		StackFrame* GetPrevious() const
		{
			return m_previous;
		}

	private:
		inline bool InTable(const string& name) const
		{
			return m_symbolTable.find(name) != m_symbolTable.end();
		}

	private:
		/*StackFrame& operator=(StackFrame&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			m_symbolTable = std::move(other.m_symbolTable);
			m_previous = other.m_previous;

			other.m_previous = nullptr;

			return *this;
		}*/

	private:
		unordered_map<string, shared_ptr<Object>> m_symbolTable;
		StackFrame* m_previous;

		friend class Stack;
	};

	class Stack {
	public:
		explicit Stack() : m_current{ new StackFrame{ nullptr } } {}

		~Stack()
		{
			if (m_current->GetPrevious())
			{
				std::cout << "Someone didn't close the stack frame" << endl;
			}

			delete m_current;
		}

		void Open()
		{
			m_current = new StackFrame(m_current);
		}

		void Close()
		{
			if (!m_current)
			{
				throw std::logic_error("Trying to close stack when it's nullptr");
			}

			StackFrame* prev = m_current->GetPrevious();
			delete m_current;
			m_current = prev;
		}

		void Set(const string& name, shared_ptr<Object> obj)
		{
			return m_current->Set(name, obj);
		}

		shared_ptr<Object> Get(const string& name) const
		{
			return m_current->Get(name);
		}

		const StackFrame* GetPrevious() const
		{
			return m_current->GetPrevious();
		}

		void Print() const
		{
			for (const auto& [name, obj] : m_current->m_symbolTable)
			{
				switch (obj->GetType())
				{
				case Type::FLOAT:
					cout << name << ": " << *((float*)obj->GetPtr()) << endl;
					break;
				case Type::INT:
					cout << name << ": " << *((int*)obj->GetPtr()) << endl;
					break;
				case Type::BOOL:
					cout << name << ": " << (*((bool*)obj->GetPtr())?"true":"false") << endl;
					break;
				case Type::NONE:
					cout << name << ": none" << endl;
					break;
				case Type::FUNCTION:
					cout << "Funcion: " << name << endl;
				default:
					break;
				}

			}
		}

	private:
		StackFrame* m_current;
	};
}