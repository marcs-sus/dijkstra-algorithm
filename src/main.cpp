#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iomanip>
#include <map>
#include <dirent.h>
#include <vector>
#include <dirent.h>

#include "nlohmann/json.hpp"

#include "graph.h"
#include "node.h"
#include "road.h"

using json = nlohmann::json;

const std::map<std::string, PavementCondition> stringToCondition = {
    {"OTIMO", PavementCondition::OTIMO},
    {"BOM", PavementCondition::BOM},
    {"RUIM", PavementCondition::RUIM}};

const std::map<std::string, PavementType> stringToType = {
    {"ASFALTO", PavementType::ASFALTO},
    {"CALCAMENTO", PavementType::CALCAMENTO},
    {"CHAO", PavementType::CHAO}};

bool loadGraphFromJson(Graph &graph, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open JSON file: " << filename << std::endl;
        return false;
    }

    json data;
    try
    {
        file >> data;
    }
    catch (json::parse_error &e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }

    std::set<std::string> createdNodes;

    for (const auto &edgeData : data["edges"])
    {
        std::string source_id = edgeData["origin"];
        std::string target_id = edgeData["destination"];

        if (createdNodes.find(source_id) == createdNodes.end())
        {
            graph.makeNode<Node>(source_id);
            createdNodes.insert(source_id);
        }

        if (createdNodes.find(target_id) == createdNodes.end())
        {
            graph.makeNode<Node>(target_id);
            createdNodes.insert(target_id);
        }

        Node *source_node = graph.findNodeById(source_id);
        Node *target_node = graph.findNodeById(target_id);

        double distance = edgeData["distance"];
        PavementCondition condition = stringToCondition.at(edgeData["estado_pavimentacao"]);
        PavementType type = stringToType.at(edgeData["tipo_pavimentacao"]);

        graph.makeEdge<Road>(*source_node, *target_node, distance, condition, type);
    }

    return true;
}

int main()
{
    Graph graph;

    try
    {
        std::vector<std::string> jsonFiles;
        std::string graphsDir = "graphs";
        DIR *dir = opendir(graphsDir.c_str());
        if (dir)
        {
            struct dirent *entry;
            while ((entry = readdir(dir)) != nullptr)
            {
                std::string fname = entry->d_name;
                if (fname.size() > 5 && fname.substr(fname.size() - 5) == ".json")
                {
                    jsonFiles.push_back(fname);
                }
            }
            closedir(dir);
        }

        if (jsonFiles.empty())
        {
            std::cerr << "No JSON files found in 'graphs' directory." << std::endl;
            return 1;
        }

        std::cout << "Available graph files:" << std::endl;
        for (size_t i = 0; i < jsonFiles.size(); ++i)
        {
            std::cout << "  [" << (i + 1) << "] " << jsonFiles[i] << std::endl;
        }

        size_t fileChoice = 0;
        while (true)
        {
            std::cout << "Select a graph file by number: ";
            std::string input;
            std::getline(std::cin, input);
            try
            {
                fileChoice = std::stoul(input);
            }
            catch (...)
            {
                fileChoice = 0;
            }
            if (fileChoice >= 1 && fileChoice <= jsonFiles.size())
                break;
            std::cout << "Invalid selection. Please try again." << std::endl;
        }

        std::string selectedFile = graphsDir + "/" + jsonFiles[fileChoice - 1];
        std::cout << "Loading graph from '" << selectedFile << "'..." << std::endl;
        if (!loadGraphFromJson(graph, selectedFile))
        {
            return 1;
        }
        std::cout << "Graph loaded successfully!" << std::endl;

        std::string sourceNode, targetNode;
        std::cout << "Enter the source node: ";
        std::getline(std::cin, sourceNode);
        std::cout << "Enter the target node: ";
        std::getline(std::cin, targetNode);

        Node *source = graph.findNodeById(sourceNode);
        Node *target = graph.findNodeById(targetNode);

        if (!source || !target)
        {
            std::cerr << "Error: Source or target node not found." << std::endl;
            return 1;
        }

        std::cout << "\nCalculating the shortest path from " << source->getId() << " to " << target->getId() << "..." << std::endl;
        auto path = graph.findShortestPathDijkstra(*source, *target);

        if (path.empty())
        {
            std::cout << "No path found." << std::endl;
        }
        else
        {
            double totalCost = 0.0;
            std::cout << "Path found:" << std::endl;
            for (Edge *edge : path)
            {
                std::cout << "  - " << edge->getSrcNode()->getId()
                          << " -> " << edge->getDstNode()->getId()
                          << " (Cost: " << std::fixed << std::setprecision(2) << edge->getWeight() << ")" << std::endl;
                totalCost += edge->getWeight();
            }
            std::cout << "Total path cost: " << std::fixed << std::setprecision(2) << totalCost << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: " << e.what() << '\n';
        return 1;
    }

    return 0;
}