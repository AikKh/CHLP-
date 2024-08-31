#include "../../h/NodeTypes/LeafNode.h"

Doer::ActionNode* Doer::LeafNode::Accept(ActionTreeGenerator& visitor) const
{
	return visitor.Visit(this);
}
