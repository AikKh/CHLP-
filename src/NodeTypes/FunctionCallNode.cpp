#include "../../h/NodeTypes/FunctionCallNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::FunctionCallNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
