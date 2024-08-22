#include "../../h/NodeTypes/LeafNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::LeafNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
