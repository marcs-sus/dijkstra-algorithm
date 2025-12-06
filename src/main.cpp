#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <dirent.h>
#include <vector>

#include "nlohmann/json.hpp"

#include "graph.h"
#include "node.h"
#include "road.h"

using json = nlohmann::json;

const std::map<std::string, PavementCondition> stringToCondition = {
    {"EXCELLENT", PavementCondition::EXCELLENT},
    {"GOOD", PavementCondition::GOOD},
    {"BAD", PavementCondition::BAD},
    {"OTIMO", PavementCondition::EXCELLENT},
    {"BOM", PavementCondition::GOOD},
    {"RUIM", PavementCondition::BAD}};

const std::map<std::string, PavementType> stringToType = {
    {"ASPHALT", PavementType::ASPHALT},
    {"PAVEMENT", PavementType::PAVEMENT},
    {"DIRT", PavementType::DIRT},
    {"ASFALTO", PavementType::ASPHALT},
    {"CALCAMENTO", PavementType::PAVEMENT},
    {"CHAO", PavementType::DIRT}};

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

    // Vector to keep track of created nodes
    std::vector<std::string> createdNodes;

    for (const auto &edgeData : data["edges"])
    {
        std::string source_id = edgeData["origin"];
        std::string target_id = edgeData["destination"];

        // Check if source node already exists
        bool sourceExists = false;
        for (const std::string &nodeId : createdNodes)
        {
            if (nodeId == source_id)
            {
                sourceExists = true;
                break;
            }
        }

        if (!sourceExists)
        {
            graph.createNode(source_id);
            createdNodes.push_back(source_id);
        }

        // Check if target node already exists
        bool targetExists = false;
        for (const std::string &nodeId : createdNodes)
        {
            if (nodeId == target_id)
            {
                targetExists = true;
                break;
            }
        }

        if (!targetExists)
        {
            graph.createNode(target_id);
            createdNodes.push_back(target_id);
        }

        Node *source_node = graph.findNodeById(source_id);
        Node *target_node = graph.findNodeById(target_id);

        double distance = edgeData["distance"];

        PavementCondition condition = stringToCondition.at(edgeData["pavement_condition"]);
        PavementType type = stringToType.at(edgeData["pavement_type"]);

        // Cria a aresta no sentido original
        graph.createRoad(source_node, target_node, distance, condition, type);

        // Adicione esta linha para criar a aresta no sentido inverso
        graph.createRoad(target_node, source_node, distance, condition, type);
    }

    return true;
}

// Main function
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

        // Call method to find the shortest path using Dijkstra's algorithm
        std::deque<Edge *> path = graph.findShortestPathDijkstra(*source, *target);

        if (path.empty())
        {
            std::cout << "No path found." << std::endl;
        }
        else
        {
            double totalCost = 0.0;
            std::cout << "Path found:" << std::endl;

            // Display the path
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
