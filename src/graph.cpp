#include "graph.h"

#include <queue>
#include <limits>
#include <string>

Node *Graph::findNodeById(const std::string &id)
{
    auto it = nodes.find(id);

    if (it == nodes.end())
    {
        return nullptr;
    }

    return (*it).get();
}

Graph::tPath Graph::findShortestPathDijkstra(const Node &src, const Node &dst)
{
    if (!findNodeById(src.getId()) || !findNodeById(dst.getId()))
    {
        throw InvalidNodeException("Source or destination node not in graph");
    }

    std::map<std::string, double> dist;

    std::map<std::string, Edge *> prev;

    std::priority_queue<std::pair<double, const Node *>,
                        std::vector<std::pair<double, const Node *>>,
                        std::greater<std::pair<double, const Node *>>>
        pq;

    double inf = std::numeric_limits<double>::infinity();

    for (const auto &np : nodes)
    {
        dist[np->getId()] = inf;
    }

    std::string srcId = src.getId();
    std::string dstId = dst.getId();
    dist[srcId] = 0;

    pq.push({0, &src});

    while (!pq.empty())
    {
        double d = pq.top().first;
        const Node *u = pq.top().second;
        pq.pop();

        std::string uId = u->getId();

        if (d > dist[uId])
        {
            continue;
        }

        for (Edge *e : u->getOutEdges())
        {
            const Node *v = e->getDstNode();
            std::string vId = v->getId();

            double alt = d + e->getWeight();

            if (alt < dist[vId])
            {
                dist[vId] = alt;
                prev[vId] = e;
                pq.push({alt, v});
            }
        }
    }

    tPath path;

    if (dist[dstId] == inf)
    {
        return path;
    }

    std::string current = dstId;
    while (current != srcId)
    {
        Edge *e = prev[current];
        if (!e)
        {
            break;
        }
        path.push_front(e);
        current = e->getSrcNode()->getId();
    }

    if (current != srcId)
    {
        path.clear();
    }

    return path;
}