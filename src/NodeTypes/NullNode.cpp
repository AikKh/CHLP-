#include "../../h/NodeTypes/NullNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::NullNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
