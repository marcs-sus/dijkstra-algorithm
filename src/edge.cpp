#include "edge.h"
#include "node.h"

Edge::Edge(Node *src, Node *dst, double w) : srcNode(src), dstNode(dst), weight(w)
{
    // Register this edge with the source and destination nodes
    if (srcNode)
    {
        srcNode->addOutEdge(this);
    }
    if (dstNode)
    {
        dstNode->addInEdge(this);
    }
}

Edge::~Edge()
{
    // Unregister this edge from the source and destination nodes
    if (srcNode)
    {
        srcNode->removeOutEdge(this);
    }
    if (dstNode)
    {
        dstNode->removeInEdge(this);
    }
}

// Check if this edge is connected to a given node
bool Edge::isConnectedTo(const Node *node) const
{
    return srcNode == node || dstNode == node;
}

// String representation of the edge (src -> dst)
std::string Edge::toString() const
{
    std::string result = "";
    if (srcNode)
    {
        result += srcNode->getId();
    }
    else
    {
        result += "NULL";
    }

    result += " -> ";

    if (dstNode)
    {
        result += dstNode->getId();
    }
    else
    {
        result += "NULL";
    }

    return result;
}
