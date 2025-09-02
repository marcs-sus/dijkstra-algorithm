<?php

declare(strict_types=1);

namespace Src;

class Graph
{
    private array $adjMatrix;
    private int $size;
    private array $vertexData;

    public function __construct($size)
    {
        $this->size = $size;
        $this->adjMatrix = [];
        for ($i = 0; $i < $size; $i++) {
            $this->adjMatrix[$i] = array_fill(0, $size, 0);
        }
        $this->vertexData = array_fill(0, $size, '');
    }

    public function AddEdge(int $u, int $v, int $weight): void
    {
        if ($u >= 0 && $u < $this->size && $v >= 0 && $v < $this->size) {
            $this->adjMatrix[$u][$v] = $weight;
            $this->adjMatrix[$v][$u] = $weight; // For undirected graph
        }
    }

    public function AddVertexData(int $vertex, string $data): void
    {
        if ($vertex >= 0 && $vertex < $this->size) {
            $this->vertexData[$vertex] = $data;
        }
    }

    public function GetSize(): int
    {
        return $this->size;
    }

    public function GetVertexData(): array
    {
        return $this->vertexData;
    }

    public function GetAdjMatrix(): array
    {
        return $this->adjMatrix;
    }
}
