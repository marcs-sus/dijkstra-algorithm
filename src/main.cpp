#include <iostream>
#include <vector>
#include <iomanip>

#include "road.h"
#include "node.h"
#include "graph.h"

int main()
{
    Graph g;

    try
    {
        Node &cidadeA = g.makeNode<Node>("Cidade A");
        Node &cidadeB = g.makeNode<Node>("Cidade B");
        Node &cidadeC = g.makeNode<Node>("Cidade C");
        Node &cidadeD = g.makeNode<Node>("Cidade D");
        Node &cidadeE = g.makeNode<Node>("Cidade E");

        g.makeEdge<Road>(cidadeA, cidadeB, 100.0, PavementCondition::OTIMO, PavementType::ASFALTO);
        g.makeEdge<Road>(cidadeA, cidadeC, 250.0, PavementCondition::RUIM, PavementType::CHAO);
        g.makeEdge<Road>(cidadeB, cidadeC, 120.0, PavementCondition::BOM, PavementType::CALCAMENTO);
        g.makeEdge<Road>(cidadeB, cidadeD, 200.0, PavementCondition::OTIMO, PavementType::ASFALTO);
        g.makeEdge<Road>(cidadeC, cidadeE, 150.0, PavementCondition::BOM, PavementType::ASFALTO);
        g.makeEdge<Road>(cidadeD, cidadeE, 80.0, PavementCondition::RUIM, PavementType::CHAO);

        Node *origem = g.findNodeById("Cidade A");
        Node *destino = g.findNodeById("Cidade E");

        if (!origem || !destino)
        {
            std::cerr << "Erro: Nó de origem ou destino não encontrado." << std::endl;
            return 1;
        }

        std::cout << "Calculando o caminho mais curto de " << origem->getId() << " para " << destino->getId() << "..." << std::endl;

        auto path = g.findShortestPathDijkstra(*origem, *destino);

        if (path.empty())
        {
            std::cout << "Nenhum caminho encontrado." << std::endl;
        }
        else
        {
            double totalCost = 0.0;
            std::cout << "Caminho encontrado:" << std::endl;
            for (Edge *edge : path)
            {
                std::cout << "  - " << edge->getSrcNode()->getId()
                          << " -> " << edge->getDstNode()->getId()
                          << " (Custo: " << std::fixed << std::setprecision(2) << edge->getWeight() << ")" << std::endl;
                totalCost += edge->getWeight();
            }
            std::cout << "Custo total do caminho: " << std::fixed << std::setprecision(2) << totalCost << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ocorreu uma exceção: " << e.what() << '\n';
        return 1;
    }

    return 0;
}