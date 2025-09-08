#pragma once
#define EDGE_H

#include <string>
#include "node.h"

class Edge
{
public:
    Edge(Node &rSrc, Node &rDst);

    Edge(const Edge &other) : Edge(other.srcNode, other.dstNode) {};

    virtual ~Edge() {};

    bool isConnectedTo(const Node &node) const;

    std::string toString() const;

    virtual double getWeight() const = 0;

    Node &getSrcNode() { return srcNode; };
    Node &getDstNode() { return dstNode; };

private:
    Node &srcNode;
    Node &dstNode;
};