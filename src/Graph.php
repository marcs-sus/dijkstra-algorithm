<?php

namespace Src;

class Graph
{
    private array $adjMatrix;
    private int $size;
    private array $vertexData;

    public function __construct($size)
    {
        $this->size = $size;
        $this->adjMatrix = array_fill(0, $size, array_fill(0, $size, 0));
        $this->vertexData = array_fill(0, $size, '');
    }

    public function AddEdge($u, $v, $weight)
    {
        if ($u >= 0 && $u < $this->size && $v >= 0 && $v < $this->size) {
            $this->adjMatrix[$u][$v] = $weight;
            $this->adjMatrix[$v][$u] = $weight; // For undirected graph
        }
    }

    public function AddVertexData($vertex, $data)
    {
        if ($vertex >= 0 && $vertex < $this->size) {
            $this->vertexData[$vertex] = $data;
        }
    }
}
