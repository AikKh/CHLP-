#include "../../h/NodeTypes/BinaryNode.h"

Doer::ActionNode* Doer::BinaryNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
