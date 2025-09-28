#pragma once

#include <list>
#include <string>
#include <deque>
#include <vector>
#include <stdexcept>

#include "node.h"
#include "edge.h"
#include "road.h"

// Custom exceptions for better error handling
class NodeCreationException : public std::runtime_error
{
public:
    explicit NodeCreationException(const std::string &msg) : std::runtime_error(msg) {}
};

class InvalidNodeException : public std::runtime_error
{
public:
    explicit InvalidNodeException(const std::string &msg) : std::runtime_error(msg) {}
};

// Graph class representing a collection of nodes and edges
class Graph
{
private:
    // Vectors to store nodes and edges
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

public:
    virtual ~Graph();

    // Methods to create nodes and edges
    Node *createNode(const std::string &id);
    Edge *createEdge(Node *srcNode, Node *dstNode, double weight = 0.0);

    // Specialized method for creating Road edges
    Road *createRoad(Node *srcNode, Node *dstNode, double distance, PavementCondition condition, PavementType type);

    // Cleanup methods
    void deleteNode(const std::string &id);
    void deleteEdge(Edge *edge);

    // Find node by ID
    Node *findNodeById(const std::string &id);

    // Method to find the shortest path using Dijkstra's algorithm
    std::deque<Edge *> findShortestPathDijkstra(const Node &src, const Node &dst);

    // Helper methods
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const { return edges.size(); }

    // Getters for all nodes and edges
    const std::vector<Node *> &getAllNodes() const { return nodes; }
    const std::vector<Edge *> &getAllEdges() const { return edges; }
};
