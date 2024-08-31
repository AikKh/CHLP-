#include "../../h/NodeTypes/FunctionCallNode.h"

Doer::ActionNode* Doer::FunctionCallNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
