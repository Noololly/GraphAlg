//
// Created by olly on 16/09/2025.
//

#include "graph.h"
#include <cstdio>

graph::graph() = default;

void graph::addEdge(int source, int destination, int weight) {
    m[source].emplace_back(destination, weight);
    m[destination].emplace_back(source, weight);
}

void graph::addVertex(const int vertex) {
    if (!m.contains(vertex)) {
        m[vertex] = std::vector<std::pair<int, int>>();
    }
}

void graph::removeEdge(int source, int destination) {
    std::erase_if(m[source], [destination](const std::pair<int, int>& p) { return p.first == destination; });
    std::erase_if(m[destination], [source](const std::pair<int, int>& p) { return p.first == source; });
}

void graph::removeVertex(const int vertex) {
    m.erase(vertex);
}

std::vector<std::pair<int, int>> graph::getNeighbours(const int source) const{
    if (const auto it = m.find(source); it != m.end()) {
        return it->second;
    }
    return {};
}


int graph::size() const {
    return static_cast<int>(m.size()); // cast from size_t to int
}

void graph::printGraph() const {
    for (const auto& [fst, snd] : m) {
        printf("%d -> ", fst);
        for (const auto&[fir, sec] : snd) {
            printf("(%d, w=%d) ", fir, sec);
        }
        printf("\n");
    }
}
