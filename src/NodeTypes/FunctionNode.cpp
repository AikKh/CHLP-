#include "../../h/NodeTypes/FunctionNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::FunctionNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
