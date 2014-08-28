#include "TreeEdgeNode.h"


TreeEdgeNode::~TreeEdgeNode()
{
}


TreeEdgeNode::TreeEdgeNode(int a, float w) : adjTreeVertex(a), weight(w), next(nullptr)
{
}