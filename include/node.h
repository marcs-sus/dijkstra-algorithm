#pragma once
#define NODE_H

#include <string>
#include <list>

class Edge;

class Node
{
public:
    Node();

    Node(std::string id);

    enum Direction
    {
        IN,
        OUT,
        BOTH
    };

    virtual ~Node() {};

    const std::string &getId() const { return id; };

    std::list<Edge *> &getOutEdges() { return outEdges; };
    std::list<Edge *> &getInEdges() { return inEdges; };

    std::list<Edge *> &getNeighbors(Direction direction = BOTH);

    virtual bool operator==(const Node &other) const { return id == other.id; };
    virtual bool operator<(const Node &other) const { return id < other.id; };

private:
    std::string id;

    std::list<Edge *> outEdges;
    std::list<Edge *> inEdges;

    static int numInstances;
};