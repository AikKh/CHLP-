#pragma once

#include "Visitor.h"
#include "Validator.h"
#include "ObjectManager.h"

// AST nodes
#include "../NodeTypes/BinaryNode.h"
#include "../NodeTypes/CompoundNode.h"
#include "../NodeTypes/UnaryNode.h"
#include "../NodeTypes/FunctionNode.h"
#include "../NodeTypes/NullNode.h"
#include "../NodeTypes/FunctionCallNode.h"

// Apt nodes
#include "../ActionNodes/AccessAction.h"
#include "../ActionNodes/AssignAction.h"
#include "../ActionNodes/ListAction.h"
#include "../ActionNodes/LiteralAction.h"
#include "../ActionNodes/OperationAction.h"
#include "../ActionNodes/NoAction.h"

namespace Doer {

	// Action tree
	class ActionTreeGenerator : public Visitor {
	public:
		/*AptGenerator() {
			_currentFrame = StackFrame::Open();
			_function = Functionality();
		}

		~AptGenerator() {
			_currentFrame->Print();
			StackFrame::Close(_currentFrame);
		}*/

		ActionTreeGenerator(StackFrame& stack_ref, const Validator& validtor) : _currentFrame{ stack_ref }, _validtor{validtor} {}

		ActionNode* Visit(const BinaryNode* node) override {
			// TODO: Refactor here
			if (IsAssignment(node)) {

				// Getting id of variable
				const LeafNode* left;
				if (!(left = dynamic_cast<const LeafNode*>(node->GetLeft()))) {
					throw std::logic_error("VALIDATOR LIED TO US");
				}

				auto right = node->GetRight()->Accept(*this);
				return new AssignAction(_currentFrame, left->GetValue().GetText(), right);
			}

			else if (operators.IsOperator(node->GetValue().GetText())) {
				return HandleOperation(node);
			}

			error.Report("Invalid operator " + node->GetValue().GetText() + " (which shouldn't be handled in this stage but anyways)",
				ErrorPriority::SOURCE_ERROR, &node->GetValue());
			return nullptr;
		}

		ActionNode* Visit(const CompoundNode* node) override {
			auto result = new ListAction();

			for (const auto& n : node->nodes) {
				result->AddAction(move(unique_ptr<ActionNode>(n->Accept(*this))));
			}

			return result;
		}

		ActionNode* Visit(const FunctionCallNode* node) override {
			throw std::logic_error("Function not yet implemented");
		}

		ActionNode* Visit(const FunctionNode* node) override {
			throw std::logic_error("Function not yet implemented");
		}

		ActionNode* Visit(const LeafNode* node) override {
			auto type = node->GetValue().GetType();

			if (type == Token::LITERAL) {
				return new LiteralAction(node->GetValue().GetText());
			}
			else if (type == Token::IDENTIFIER) {
				return new AccessAction(_currentFrame, node->GetValue().GetText());
			}

			error.Report("Invalid token " + node->GetValue().GetText() + " (which also shouldn't be handled in this stage)",
				ErrorPriority::SOURCE_ERROR, &node->GetValue());
			return nullptr;
		}

		ActionNode* Visit(const NullNode* node) override {
			return new NoAction();
		}

		ActionNode* Visit(const UnaryNode* node) override {
			throw std::logic_error("Function not yet implemented");
		}

	private:
		inline bool IsAssignment(const BinaryNode* node)
		{
			if (node->GetValue().GetText() == "=")
			{
				if (_validtor.IsVariable(node->GetLeft()))
				{
					return true;
				}

				return false;
			}

			return false;
		}

		OperationAction* HandleOperation(const BinaryNode* node) {
			auto operand1 = node->GetLeft()->Accept(*this);
			auto operand2 = node->GetRight()->Accept(*this);
			auto& text = node->GetValue().GetText();

			OperatorId id{};
			if (operators.SearchOperatorId(text, id))
			{
				return new OperationAction(operand1, operand2, id);
			}

			error.Report("Unknown operator: " + text, ErrorPriority::SOURCE_ERROR);
			return nullptr;
		}

	private:
		StackFrame& _currentFrame;
		const Validator& _validtor;
	};
}