#include "edge.h"
#include "node.h"

Edge::Edge(Node &rSrc, Node &rDst) : srcNode(&rSrc), dstNode(&rDst)
{
    srcNode->getOutEdges().push_back(this);
    dstNode->getInEdges().push_back(this);
}

Edge::~Edge()
{
    if (srcNode)
    {
        srcNode->getOutEdges().remove(this);
    }
    if (dstNode)
    {
        dstNode->getInEdges().remove(this);
    }
}

bool Edge::isConnectedTo(const Node &node) const
{
    return srcNode == &node || dstNode == &node;
}

std::string Edge::toString() const
{
    return srcNode->getId() + " -> " + dstNode->getId();
}