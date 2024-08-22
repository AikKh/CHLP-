#pragma once

#include "Object.h"
#include "../ErrorHandler.h"

namespace Doer {

	struct VariableInfo {
		Type type;
		unsigned int address;

		VariableInfo(const Type& type, int address) : type(type), address(address) { }

		VariableInfo() : VariableInfo(Type::Get(TypeId::VOID), 0) {}

		VariableInfo(const VariableInfo& other) : VariableInfo(other.type, other.address) {}
	};

	class StackFrame {
	public:
		static StackFrame* Open(StackFrame* previous = nullptr) {
			return new StackFrame(previous);
		}

		static void Close(StackFrame*& current) {
			delete current;
			current = current->_previous;
		}

		void Set(string name, const Type& type, void* valueAddress) {
			if (!InTable(name)) {
				Add(name, type);
			}

			int address = GetAddress(name);

			// TODO: Refactor into separete method
			if (type.GetSize() != GetType(name).GetSize()) {
				auto ptr = realloc(_stack[address], type.GetSize());

				if (ptr == nullptr) {
					throw std::runtime_error("Failed to reallocate memory");
				}
				_stack[address] = ptr;
				_symbolTable.at(name).type = type;
			}

			std::memcpy(_stack[address], valueAddress, type.GetSize());

		}

		// TODO: return the var type, like Type*& type
		VariableInfo GetInfo(const string& name) {
			if (InTable(name)) {
				return _symbolTable[name];
			}

			error.Report("The variable " + name + " is not declared", ErrorPriority::RUNTIME_ERROR);
			return VariableInfo(Type::Get(TypeId::VOID), -1);
		}

		inline const void* GetPtrByStackAddress(int address) {
			return _stack[address];
		}

		inline const Type& GetType(const string& name) {
			return _symbolTable.at(name).type;
		}

	private:
		StackFrame(StackFrame* previous) : _previous(previous) {
			cout << "Stack frame opened" << endl;
		}

		~StackFrame() {
			cout << "Stack frame closed" << endl;
			for (auto& ptr : _stack) {
				delete ptr;
			}
		}

		void Add(string name, const Type& type) {
			void* address = malloc(type.GetSize());
			_stack.push_back(address);

			_symbolTable[name] = VariableInfo(type, _stack.size() - 1);
		}

		inline bool InTable(const string& name) {
			return _symbolTable.find(name) != _symbolTable.end();
		}

		inline int GetAddress(const string& name) {
			return _symbolTable.at(name).address;
		}

	public:

		void Print() {
			for (const auto& pair : _symbolTable) {
				cout << pair.first << ": " << *((int*)_stack[pair.second.address]) << endl;
			}
		}

	private:

		unordered_map<string, VariableInfo> _symbolTable;
		vector<void*> _stack;

		StackFrame* _previous;
	};
}