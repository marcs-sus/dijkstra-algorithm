#pragma once
#define NODE_H

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
    struct SortNodeById
    {
        bool operator()(const Node *l, const Node *r) const
        {
            return l->getId() < r->getId();
        }
    };

    typedef std::set<Node *, SortNodeById> tNodePtrSet;
    typedef std::list<Edge *> tEdgePtrList;
    typedef std::deque<Edge *> tPath;
    typedef std::vector<Edge *> tEdges;
    typedef std::vector<Node *> tNodes;

    struct DijkstraInfo
    {
        double distance;
        Node *prevNode;
        Edge *prevEdge;
    };

    typedef std::map<Node *, DijkstraInfo> tDijkstraMap;

public:
    class Exception;
    class NodeCreationException;
    class InvalidNodeException;
    class NotFoundException;

    virtual ~Graph();

    template <class T>
    T &makeNode(T &node);

    template <class T, class... Args>
    T &makeNode(Args &&...args) { return makeNode(T(std::forward<Args>)) };

    template <class T>
    T &makeEdge(T &edge);

    template <class T, class... Args>
    T &makeEdge(Args &&...args) { return makeEdge(T(std::forward<Args>(args)...)); }

    template <class T, class... Args>
    void makeBiEdge(Node &n1, Node &n2, Args &&...args)
    {
        makeEdge(T(n1, n2, std::forward<Args>(args)...));
        makeEdge(T(n2, n1, std::forward<Args>(args)...));
    }

    template <class T>
    Graph &operator<<(T &&edge)
    {
        makeEdge(std::move(edge)) return *this;
    }

    tNodePtrSet &getNode() { return nodes; }

    bool remove(const Edge &edge);

    bool remove(const Node &node);

    Node *Graph::findNodeById(const std::string &id);

    tEdges findEdges(const Node &src, const Node &dst);

    tEdges findEdges(const std::string &srcId, const std::string &dstId);

    std::string toString() const;

    void saveAsDot(const std::string &filename) const;

    tDijkstraMap findDistancesDijkstra(const Node &srcNode, const Node *dstNode, Node **foundDst);

    tPath findShortestPathDijkstra(const Node &src, const Node &dst);

protected:
    tNodePtrSet nodes;
    tEdgePtrList edges;
};

class Graph::Exception
{
public:
    Exception(const std::string &what) : what(what) {}
    virtual ~Exception() {}
    const std::string &what() const { return what; }

private:
    std::string what;
};

class Graph::NodeCreationException : public Graph::Exception
{
public:
    NodeCreationException(const std::string &what) : Exception(what) {}
};

class Graph::InvalidNodeException : public Graph::Exception
{
public:
    InvalidNodeException(const std::string &what) : Exception(what) {}
};

class Graph::NotFoundException : public Graph::Exception
{
public:
    NotFoundException(const std::string &what) : Exception(what) {}
};

template <class T>
T &Graph::makeNode(T &&node)
{
    auto it = m_nodes.lower_bound(&node);
    if (it != m_nodes.end() && (*it)->getId() == node.getId())
    {
        throw NodeCreationException("NodeID is not unique: " + node.getId());
    }

    auto ret = m_nodes.insert(it, new T(std::move(node)));

    return **ret;
}

template <class T>
T &Graph::makeEdge(T &&edge)
{
    if (std::find(m_nodes.begin(), m_nodes.end(), &edge.getDstNode()) == m_nodes.end())
    {
        throw InvalidNodeException("source node is not in the graph");
    }

    if (std::find(m_nodes.begin(), m_nodes.end(), &edge.getSrcNode()) == m_nodes.end())
    {
        throw InvalidNodeException("destination node is not in the graph");
    }

    T *newEdge = new T(std::move(edge));
    m_edges.push_back(newEdge);
    return *newEdge;
}