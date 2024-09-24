#pragma once

#include <memory>

namespace Doer 
{
	class Stack;
	class Validator;

	class BinaryNode;
	class CompoundNode;
	class FunctionCallNode;
	class FunctionNode;
	class IfNode;
	class LeafNode;
	class NullNode;
	class ReturnNode;
	class UnaryNode;

	class ActionNode;

	class ActionTreeGenerator {
	public:
		ActionTreeGenerator(std::shared_ptr<Stack> stack, const Validator& validtor);

		ActionNode* Visit(const BinaryNode* node);

		ActionNode* Visit(const CompoundNode* node);

		ActionNode* Visit(const FunctionCallNode* node);

		ActionNode* Visit(const FunctionNode* node);

		ActionNode* Visit(const LeafNode* node);

		ActionNode* Visit(const NullNode* node);

		ActionNode* Visit(const UnaryNode* node);

		ActionNode* Visit(const IfNode* node);

		ActionNode* Visit(const ReturnNode* node);

	private:
		inline bool IsAssignment(const BinaryNode* node);

		ActionNode* HandleOperation(const BinaryNode* node);

	private:
		std::shared_ptr<Stack> m_stack;
		const Validator& m_validtor;
	};
}