#include "../../h/NodeTypes/IfNode.h"

Doer::ActionNode* Doer::IfNode::Accept(ActionTreeGenerator& visitor) const
{
    return visitor.Visit(this);
}
