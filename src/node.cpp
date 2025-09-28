#include "node.h"
#include "edge.h"

void Node::addOutEdge(Edge *edge)
{
    // Linear search to avoid duplicates
    for (Edge *existingEdge : outEdges)
    {
        // If already exists, don't add again
        if (existingEdge == edge)
        {
            return;
        }
    }

    outEdges.push_back(edge);
}

void Node::addInEdge(Edge *edge)
{
    // Linear search to avoid duplicates
    for (Edge *existingEdge : inEdges)
    {
        // If already exists, don't add again
        if (existingEdge == edge)
        {
            return;
        }
    }

    inEdges.push_back(edge);
}

void Node::removeOutEdge(Edge *edge)
{
    // Linear search and removal
    for (int i = 0; i < outEdges.size(); i++)
    {
        if (outEdges[i] == edge)
        {
            outEdges.erase(outEdges.begin() + i);
            break;
        }
    }
}

void Node::removeInEdge(Edge *edge)
{
    // Linear search and removal
    for (int i = 0; i < inEdges.size(); i++)
    {
        if (inEdges[i] == edge)
        {
            inEdges.erase(inEdges.begin() + i);
            break;
        }
    }
}
