#include "graph.h"
#include "road.h"

#include <string>
#include <limits>

Graph::~Graph()
{
    // Clean up all edges first
    for (Edge *edge : edges)
    {
        delete edge;
    }
    edges.clear();

    // Then clean up all nodes
    for (Node *node : nodes)
    {
        delete node;
    }
    nodes.clear();
}

Node *Graph::createNode(const std::string &id)
{
    // Check if node with this ID already exists
    for (Node *existingNode : nodes)
    {
        if (existingNode->getId() == id)
        {
            throw NodeCreationException("NodeID is not unique: " + id);
        }
    }

    // Create new node and add to vector
    Node *newNode = new Node(id);
    nodes.push_back(newNode);

    return newNode;
}

Edge *Graph::createEdge(Node *srcNode, Node *dstNode, double weight)
{
    // Check if both nodes exist in the graph
    if (!findNodeById(srcNode->getId()))
    {
        throw InvalidNodeException("source node is not in the graph");
    }
    if (!findNodeById(dstNode->getId()))
    {
        throw InvalidNodeException("destination node is not in the graph");
    }

    Edge *newEdge = new Edge(srcNode, dstNode);
    edges.push_back(newEdge);

    return newEdge;
}

void Graph::deleteNode(const std::string &id)
{
    // Find and remove node from vector
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getId() == id)
        {
            delete nodes[i];
            nodes.erase(nodes.begin() + i);
            break;
        }
    }

    // Remove any edges connected to this node
    for (int i = edges.size() - 1; i >= 0; i--)
    {
        Edge *edge = edges[i];
        if (edge->getSrcNode()->getId() == id || edge->getDstNode()->getId() == id)
        {
            delete edge;
            edges.erase(edges.begin() + i);
        }
    }
}

void Graph::deleteEdge(Edge *edge)
{
    // Find and remove edge from vector
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i] == edge)
        {
            delete edges[i];
            edges.erase(edges.begin() + i);
            break;
        }
    }
}

Node *Graph::findNodeById(const std::string &id)
{
    // Linear search through vector
    for (Node *node : nodes)
    {
        if (node->getId() == id)
        {
            return node;
        }
    }

    return nullptr;
}

std::deque<Edge *> Graph::findShortestPathDijkstra(const Node &src, const Node &dst)
{
    // Define infinity
    const double infinity = std::numeric_limits<double>::infinity();

    // Check if both nodes exist in the graph
    if (!findNodeById(src.getId()) || !findNodeById(dst.getId()))
    {
        throw InvalidNodeException("Source or destination node not in graph");
    }

    // Vectors for Dijkstra's algorithm
    std::vector<std::string> nodeIds;
    std::vector<double> distances;
    std::vector<Edge *> previousEdges;
    std::vector<bool> visited;

    // Build list of all node IDs for easy indexing
    for (Node *node : nodes)
    {
        nodeIds.push_back(node->getId());
        distances.push_back(infinity);
        previousEdges.push_back(nullptr);
        visited.push_back(false);
    }

    // Helper function to find index of node ID
    auto findNodeIndex = [&](const std::string &id) -> int
    {
        for (int i = 0; i < nodeIds.size(); i++)
        {
            if (nodeIds[i] == id)
                return i;
        }
        return -1;
    };

    int srcIndex = findNodeIndex(src.getId());
    int dstIndex = findNodeIndex(dst.getId());

    // Set source distance to 0
    distances[srcIndex] = 0.0;

    // Main Dijkstra loop
    for (int count = 0; count < nodes.size(); count++)
    {
        // Find unvisited node with minimum distance
        int minIndex = -1;
        double minDistance = infinity;

        for (int i = 0; i < nodes.size(); i++)
        {
            if (!visited[i] && distances[i] < minDistance)
            {
                minDistance = distances[i];
                minIndex = i;
            }
        }

        // If no reachable unvisited node found, break
        if (minIndex == -1)
            break;

        // Mark current node as visited
        visited[minIndex] = true;

        // Find the actual node object
        Node *currentNode = findNodeById(nodeIds[minIndex]);

        // Check all neighbors of current node
        for (Edge *edge : currentNode->getOutEdges())
        {
            Node *neighborNode = edge->getDstNode();
            int neighborIndex = findNodeIndex(neighborNode->getId());

            if (!visited[neighborIndex])
            {
                double newDistance = distances[minIndex] + edge->getWeight();

                // If we found a shorter path to the neighbor
                if (newDistance < distances[neighborIndex])
                {
                    distances[neighborIndex] = newDistance;
                    previousEdges[neighborIndex] = edge;
                }
            }
        }
    }

    // Build the path by backtracking
    std::deque<Edge *> shortestPath;

    // If destination is unreachable, return empty path
    if (distances[dstIndex] >= infinity)
    {
        return shortestPath;
    }

    // Reconstruct path from destination back to source
    int currentIndex = dstIndex;
    while (currentIndex != srcIndex)
    {
        Edge *edgeToAdd = previousEdges[currentIndex];

        // If no path found, break
        if (!edgeToAdd)
        {
            break;
        }

        shortestPath.push_front(edgeToAdd);
        currentIndex = findNodeIndex(edgeToAdd->getSrcNode()->getId());
    }

    // Check if the source node was reached
    if (currentIndex != srcIndex)
    {
        shortestPath.clear();
    }

    return shortestPath;
}

Road *Graph::createRoad(Node *srcNode, Node *dstNode, double distance, PavementCondition condition, PavementType type)
{
    // Check if both nodes exist in the graph
    if (!findNodeById(srcNode->getId()))
    {
        throw InvalidNodeException("source node is not in the graph");
    }
    if (!findNodeById(dstNode->getId()))
    {
        throw InvalidNodeException("destination node is not in the graph");
    }

    // Create new road edge with all road-specific properties
    Road *newRoad = new Road(srcNode, dstNode, distance, condition, type);
    edges.push_back(newRoad);

    return newRoad;
}
