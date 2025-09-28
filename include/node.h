#pragma once

#include <string>
#include <vector>

class Edge;

// Node class representing a graph node
class Node
{
public:
    Node(const std::string &id) : id(id) {}

    // Getter for node ID
    const std::string &getId() const { return id; }

    // Getters for incoming and outgoing edges - using simple vectors instead of lists
    const std::vector<Edge *> &getOutEdges() const { return outEdges; }
    const std::vector<Edge *> &getInEdges() const { return inEdges; }

    // Methods to manage edges
    void addOutEdge(Edge *edge);
    void addInEdge(Edge *edge);
    void removeOutEdge(Edge *edge);
    void removeInEdge(Edge *edge);

    // Comparison operators
    bool operator==(const Node &other) const { return id == other.id; }
    bool operator<(const Node &other) const { return id < other.id; }

private:
    // Node unique identifier
    std::string id;

    // Simple vectors instead of lists for edges
    std::vector<Edge *> outEdges;
    std::vector<Edge *> inEdges;
};
