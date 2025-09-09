#pragma once

#include <string>
#include <list>

class Edge;

class Node
{
public:
    friend class Edge;
    friend class Graph;

    Node(std::string id);

    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    virtual ~Node() = default;

    const std::string &getId() const { return id; }

    // Lists of incoming and outgoing edges
    const std::list<Edge *> &getOutEdges() const { return outEdges; }
    const std::list<Edge *> &getInEdges() const { return inEdges; }

    // Operators for comparison based on ID
    bool operator==(const Node &other) const { return id == other.id; }
    bool operator<(const Node &other) const { return id < other.id; }

private:
    std::list<Edge *> &getOutEdges() { return outEdges; }
    std::list<Edge *> &getInEdges() { return inEdges; }

    std::string id;
    std::list<Edge *> outEdges;
    std::list<Edge *> inEdges;
};