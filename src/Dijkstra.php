<?php

declare(strict_types=1);

namespace Src;

use \Src\Graph;
use \Src\Helpers;
use \Src\NoPathException;

class Dijkstra
{
    private Graph $graph;

    public function __construct(Graph $graph)
    {
        $this->graph = $graph;
    }

    public function FindShortestPath(string $startVertexData): array
    {
        $vertexData = $this->graph->GetVertexData();
        $size = $this->graph->GetSize();
        $adjMatrix = $this->graph->GetAdjMatrix();

        // Find index of the start vertex
        $startVertex = -1;
        for ($i = 0; $i < $size; $i++) {
            if ($vertexData[$i] === $startVertexData) {
                $start_vertex = $i;
                break;
            }
        }

        if ($start_vertex === -1) {
            return []; // Return empty array if start vertex not found
        }

        // Initialize distances with PHP equivalent of float('inf')
        $distances = array_fill(0, $size, PHP_INT_MAX);
        $distances[$start_vertex] = 0;

        // Initialize visited array
        $visited = array_fill(0, $size, false);

        for ($count = 0; $count < $size; $count++) {
            $min_distance = PHP_INT_MAX;
            $u = null;

            // Find the unvisited vertex with minimum distance
            for ($i = 0; $i < $size; $i++) {
                if (!$visited[$i] && $distances[$i] < $min_distance) {
                    $min_distance = $distances[$i];
                    $u = $i;
                }
            }

            // If no unvisited vertex found, break
            if ($u === null) {
                break;
            }

            $visited[$u] = true;

            // Update distances for adjacent vertices
            for ($v = 0; $v < $size; $v++) {
                if ($adjMatrix[$u][$v] !== 0 && !$visited[$v]) {
                    $alt = $distances[$u] + $adjMatrix[$u][$v];
                    if ($alt < $distances[$v]) {
                        $distances[$v] = $alt;
                    }
                }
            }
        }

        return $distances;
    }
}
