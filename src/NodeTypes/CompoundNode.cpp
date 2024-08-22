#include "../../h/NodeTypes/CompoundNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::CompoundNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
