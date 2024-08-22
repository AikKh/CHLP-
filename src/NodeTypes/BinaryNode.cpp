#include "../../h/NodeTypes/BinaryNode.h"
#include "../../h/Interpretation/Visitor.h"

Doer::ActionNode* Doer::BinaryNode::Accept(Doer::Visitor& visitor) const
{
	return visitor.Visit(this);
}
