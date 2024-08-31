#include "../../h/NodeTypes/FunctionNode.h"

Doer::ActionNode* Doer::FunctionNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
