#pragma once

#define RETURN_TYPE ActionNode*

namespace Doer {
	class BinaryNode;
	class CompoundNode;
	class FunctionCallNode;
	class FunctionNode;
	class LeafNode;
	class NullNode;
	class UnaryNode;
}

namespace Doer {
	class ActionNode;
}

namespace Doer {

	class Visitor { 
	public:
		virtual RETURN_TYPE Visit(const BinaryNode* node) = 0;
		virtual RETURN_TYPE Visit(const CompoundNode* node) = 0;
		virtual RETURN_TYPE Visit(const FunctionCallNode* node) = 0;
		virtual RETURN_TYPE Visit(const FunctionNode* node) = 0;
		virtual RETURN_TYPE Visit(const LeafNode* node) = 0;
		virtual RETURN_TYPE Visit(const NullNode* node) = 0;
		virtual RETURN_TYPE Visit(const UnaryNode* node) = 0;
	};
}
