#include "../../h/NodeTypes/UnaryNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::UnaryNode::Accept(Visitor& visitor) const
{
	return visitor.Visit(this);
}
