#pragma once

#include <list>
#include <string>
#include <deque>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

#include "node.h"
#include "edge.h"

class Graph
{
private:
    struct SortNodePtrById
    {
        using is_transparent = void;
        bool operator()(const std::unique_ptr<Node> &l, const std::unique_ptr<Node> &r) const { return l->getId() < r->getId(); }
        bool operator()(const std::unique_ptr<Node> &l, const std::string &r_id) const { return l->getId() < r_id; }
        bool operator()(const std::string &l_id, const std::unique_ptr<Node> &r) const { return l_id < r->getId(); }
    };

    // Type aliases
    using tNodePtrSet = std::set<std::unique_ptr<Node>, SortNodePtrById>;
    using tEdgePtrList = std::list<std::unique_ptr<Edge>>;
    using tPath = std::deque<Edge *>;

public:
    virtual ~Graph() = default;

    template <class T, class... Args>
    T &makeNode(Args &&...args);

    template <class T, class... Args>
    T &makeEdge(Args &&...args);

    Node *findNodeById(const std::string &id);

    tPath findShortestPathDijkstra(const Node &src, const Node &dst);

protected:
    tNodePtrSet nodes;
    tEdgePtrList edges;
};

// Template implementations
template <class T, class... Args>
T &Graph::makeNode(Args &&...args)
{
    auto newNode = std::make_unique<T>(std::forward<Args>(args)...);

    // Check if a node with the same ID already exists
    auto it = nodes.find(newNode->getId());
    if (it != nodes.end())
    {
        throw NodeCreationException("NodeID is not unique: " + newNode->getId());
    }

    // Move pointer ownership to the set
    auto result = nodes.insert(std::move(newNode));

    // Return the reference to the newly created node
    return static_cast<T &>(**result.first);
}

template <class T, class... Args>
T &Graph::makeEdge(Args &&...args)
{
    auto newEdge = std::make_unique<T>(std::forward<Args>(args)...);

    if (!findNodeById(newEdge->getSrcNode()->getId()))
    {
        throw InvalidNodeException("source node is not in the graph");
    }
    if (!findNodeById(newEdge->getDstNode()->getId()))
    {
        throw InvalidNodeException("destination node is not in the graph");
    }

    edges.push_back(std::move(newEdge));
    return static_cast<T &>(*edges.back());
}