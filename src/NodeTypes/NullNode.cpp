#include "../../h/NodeTypes/NullNode.h"

Doer::ActionNode* Doer::NullNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
