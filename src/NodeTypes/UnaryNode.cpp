#include "../../h/NodeTypes/UnaryNode.h"

Doer::ActionNode* Doer::UnaryNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
