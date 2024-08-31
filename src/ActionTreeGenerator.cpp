#include "../h/Interpretation/ActionTreeGenerator.h"
#include "../h/AllOperators.h"
#include "../h/MemoryManagement/StackFrame.h"

// AST nodes
#include "../h/NodeTypes/BinaryNode.h"
#include "../h/NodeTypes/CompoundNode.h"
#include "../h/NodeTypes/FunctionCallNode.h"
#include "../h/NodeTypes/FunctionNode.h"
#include "../h/NodeTypes/IfNode.h"
#include "../h/NodeTypes/LeafNode.h"
#include "../h/NodeTypes/NullNode.h"
#include "../h/NodeTypes/ReturnNode.h"
#include "../h/NodeTypes/UnaryNode.h"

// Apt nodes
#include "../h/ActionNodes/AccessAction.h"
#include "../h/ActionNodes/AssignAction.h"
#include "../h/ActionNodes/IfAction.h"
#include "../h/ActionNodes/FunctionAction.h"
#include "../h/ActionNodes/FunctionCallAction.h"
#include "../h/ActionNodes/CompoundAction.h"
#include "../h/ActionNodes/LiteralAction.h"
#include "../h/ActionNodes/NoAction.h"
#include "../h/ActionNodes/OperationAction.h"
#include "../h/ActionNodes/ReturnAction.h"

#include "../h/Interpretation/Validator.h"

namespace Doer
{
	ActionTreeGenerator::ActionTreeGenerator(StackFrame*& stack_ref, const Validator& validtor) : m_currentStack{ stack_ref }, m_validtor{ validtor } {}

	ActionNode* Doer::ActionTreeGenerator::Visit(const BinaryNode* node)
	{
		if (IsAssignment(node))
		{
			// Getting id of variable
			const LeafNode* left;
			if (!(left = dynamic_cast<const LeafNode*>(node->GetLeft())))
			{
				throw std::logic_error("VALIDATOR LIED TO US");
			}
		
			auto right = node->GetRight()->Accept(*this);
			return new AssignAction(m_currentStack, left->GetValue().GetText(), right);
		}
		
		else if (operators.IsOperator(node->GetValue().GetText()))
		{
			return HandleOperation(node);
		}
		
		error.Report("Invalid operator " + node->GetValue().GetText() + " (which shouldn't be handled in this stage but anyways)",
			ErrorPriority::SOURCE_ERROR, &node->GetValue());
		return nullptr;
	}

	ActionNode* ActionTreeGenerator::Visit(const CompoundNode* node)
	{
		auto result = new CompoundAction();

		for (const auto& n : node->nodes)
		{
			result->AddAction(std::move(unique_ptr<ActionNode>(n->Accept(*this))));
		}

		return result;
	}

	ActionNode* ActionTreeGenerator::Visit(const FunctionCallNode* node)
	{
		auto get_func = std::unique_ptr<ActionNode>(node->GetValue()->Accept(*this));

		auto args_node = dynamic_cast<const CompoundNode*>(node->GetArgs());

		if (args_node == nullptr)
		{
			throw std::logic_error("Function call argument node should be compound node");
		}

		vector<unique_ptr<ActionNode>> args;

		for (auto n : args_node->nodes)
		{
			args.push_back(unique_ptr<ActionNode>(n->Accept(*this)));
		}

		return new FunctioCallAction(m_currentStack, std::move(get_func), std::move(args));
	}


	ActionNode* ActionTreeGenerator::Visit(const FunctionNode* node)
	{
		vector<string> args;

		for (auto n : node->GetArgs()->nodes) // friend with Action tree generator
		{
			auto arg = dynamic_cast<LeafNode*>(n);
			if (arg)
			{
				args.push_back(std::move(*arg).GetValue().GetText());
			}
			else
			{
				throw std::logic_error("Argument node should be leaf node. Probably something went wrong in parser");
			}
		}

		auto body = unique_ptr<ActionNode>(node->GetBody()->Accept(*this));
		
		return new FunctionAction(m_currentStack, node->GetName(), std::move(args), std::move(body));
	}


	ActionNode* ActionTreeGenerator::Visit(const LeafNode* node)
	{
		auto type = node->GetValue().GetType();

		if (type == Token::LITERAL || type == Token::BOOLEAN)
		{
			return new LiteralAction(node->GetValue().GetText(), type == Token::BOOLEAN);
		}
		else if (type == Token::IDENTIFIER)
		{
			return new AccessAction(m_currentStack, node->GetValue().GetText());
		}

		error.Report("Invalid token " + node->GetValue().GetText() + " (which also shouldn't be handled in this stage)",
			ErrorPriority::SOURCE_ERROR, &node->GetValue());
		return nullptr;
	}

	ActionNode* ActionTreeGenerator::Visit(const NullNode* node)
	{
		throw std::logic_error("This function is not implemented");
	}

	ActionNode* ActionTreeGenerator::Visit(const UnaryNode* node)
	{
		throw std::logic_error("This function is not implemented");
	}

	ActionNode* ActionTreeGenerator::Visit(const IfNode* node)
	{
		vector <unique_ptr< ActionNode >> m_conditions;
		vector <unique_ptr< ActionNode >> m_bodies;
		unique_ptr<ActionNode> m_else{};

		for (auto cond : node->GetConditions())
		{
			m_conditions.push_back(unique_ptr<ActionNode>(cond->Accept(*this)));
		}

		for (auto body : node->GetBodies())
		{
			m_bodies.push_back(unique_ptr<ActionNode>(body->Accept(*this)));
		}

		if (node->GetElseBody())
		{
			m_else = unique_ptr<ActionNode>(node->GetElseBody()->Accept(*this));
		}

		return new IfAction(std::move(m_conditions), std::move(m_bodies), std::move(m_else), m_currentStack);
	}

	ActionNode* ActionTreeGenerator::Visit(const ReturnNode* node)
	{
		ActionNode* action = node->GetExpression()->Accept(*this);
		return new ReturnAction(action, m_currentStack);
	}

	inline bool ActionTreeGenerator::IsAssignment(const BinaryNode* node)
	{
		if (node->GetValue().GetText() == "=")
		{
			if (m_validtor.IsVariable(node->GetLeft()))
			{
				return true;
			}

			return false;
		}

		return false;
	}

	ActionNode* ActionTreeGenerator::HandleOperation(const BinaryNode* node)
	{
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
}

