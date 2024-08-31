#include "../../h/NodeTypes/ReturnNode.h"

Doer::ActionNode* Doer::ReturnNode::Accept(ActionTreeGenerator& visitor) const
{
    return visitor.Visit(this);
}
