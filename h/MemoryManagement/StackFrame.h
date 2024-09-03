#pragma once

#include "Object.h"
#include "../ErrorHandler.h"

namespace Doer {

	class StackFrame {
	public:
		static StackFrame* Open(StackFrame* previous = nullptr) {
			return new StackFrame(previous);
		}

		static StackFrame* Close(StackFrame* current) {
			auto prev = current->_previous;
			delete current;
			return prev;
		}

		void Set(const string& name, shared_ptr<Object> obj) {
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

		const StackFrame* GetPrevious() const
		{
			return _previous;
		}

	private:
		StackFrame(StackFrame* previous) : _previous(previous) {
			//cout << "Stack frame opened" << endl;
		}

		~StackFrame() {
			//cout << "Stack frame closed" << endl;
		}

		inline bool InTable(const string& name) const {
			return m_symbolTable.find(name) != m_symbolTable.end();
		}

	public:
		void Print() {
			for (const auto& [name, obj] : m_symbolTable) {
				switch (obj->GetType())
				{
				case Type::FLOAT:
					cout << name << ": " << *((float*)obj->GetPtr()) << endl;
					break;
				case Type::INT:
					cout << name << ": " << *((int*)obj->GetPtr()) << endl;
					break;
				case Type::BOOL:
					cout << name << ": " << (*((bool*)obj->GetPtr()) ? "true" : "false") << endl;
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
		unordered_map<string, shared_ptr<Object>> m_symbolTable;
		StackFrame* _previous;
	};
}