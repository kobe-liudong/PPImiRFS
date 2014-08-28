#include "EdgeNode.h"


EdgeNode::~EdgeNode()
{
}


EdgeNode::EdgeNode(int a, float w) : adjVertex(a), weight(w), next(nullptr)
{
}