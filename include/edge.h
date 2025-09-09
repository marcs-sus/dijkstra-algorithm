#pragma once

#include <string>

class Node;

class Edge {
public:
    Edge(Node& rSrc, Node& rDst);

    Edge(const Edge& other) = default;
    virtual ~Edge() = default;

    bool isConnectedTo(const Node& node) const;
    std::string toString() const;

    virtual double getWeight() const = 0;

    const Node* getSrcNode() const { return srcNode; };
    const Node* getDstNode() const { return dstNode; };

    Node* getSrcNode() { return srcNode; };
    Node* getDstNode() { return dstNode; };

private:
    Node* srcNode;
    Node* dstNode;
};