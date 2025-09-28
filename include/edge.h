#pragma once

#include <string>

class Node;

// Edge class representing a connection between two nodes
class Edge
{
public:
    Edge(Node *src, Node *dst, double weight = 0.0);
    virtual ~Edge();

    // Check if the edge is connected to a given node
    bool isConnectedTo(const Node *node) const;

    // Virtual method to get the weight of the edge
    virtual double getWeight() const { return weight; }

    // Const getters for source and destination nodes
    const Node *getSrcNode() const { return srcNode; }
    const Node *getDstNode() const { return dstNode; }

    // Non-const getters (needed for some operations)
    Node *getSrcNode() { return srcNode; }
    Node *getDstNode() { return dstNode; }

    // String representation of the edge
    std::string toString() const;

protected:
    // Protected so derived classes can access it
    double weight;

private:
    // Pointers to the source and destination nodes
    Node *srcNode;
    Node *dstNode;
};
