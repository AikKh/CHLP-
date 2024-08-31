#include "../../h/NodeTypes/CompoundNode.h"

Doer::ActionNode* Doer::CompoundNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
