#pragma once

#include "../Node.h"
#include "../Mode.h"
#include "CompoundNode.h"

namespace Doer {

	class FunctionNode : public Node {
	public:

		FunctionNode(string id, ModeData mode, Node* body, Node* returnValue)
			: _mode(mode), _body(body), _return(returnValue), _id(id)
		{
			_hasName = !id.empty();

			if (body == nullptr && returnValue == nullptr) {
				//throw std::logic_error("Function can't be without body and return value");
				error.Report("Function can't be without body and return value", ErrorPriority::SOURCE_ERROR);
			}
		}

		~FunctionNode() override {
			delete _body;
		}

		void Print(int level = 0) const override {
			string ind = string(level, ' ');

			cout << ind << ModeToString(_mode.GetMode()) + " function: " << endl;

			if (_hasName) {
				cout << ind << "Id: " << _id << endl;
			}

			if (_mode.HasValue()) {
				cout << ind << "Mode value: " << endl;
				_mode.GetValue()->Print(level + Indedention);
			}

			if (_body)
			{
				cout << ind << "Body:" << endl;
				_body->Print(level + Indedention);
			}
			if (_return)
			{
				cout << ind << "Return:" << endl;
				_return->Print(level + Indedention);
			}
		}

		ActionNode* Accept(Visitor& runner) const override;

		bool HasName() const {
			return _hasName;
		}

		string GetName() const {
			if (!_hasName) {
				throw std::logic_error("The function node does not have a name.");
			}
			return _id;
		}

		const ModeData& GetMode() const {
			return _mode;
		}

	private:
		string _id;
		ModeData _mode;

		Node* _body;
		Node* _return;

		bool _hasName = false;


	public:
		static Mode GetMode(char m) {
			switch (m)
			{
			case '!':
				return IMMEDIATE;
			case '?':
				return CONDITIONAL;
			default:
				return REGULAR;
			}
		}

		static string ModeToString(Mode mode) {
			switch (mode)
			{
			case IMMEDIATE:
				return "Immediate";
			case CONDITIONAL:
				return "Conditional";
			case REGULAR:
				return "Regular";
			default:
				throw std::exception("Unrecognized mode");
			}
		}
	};
}