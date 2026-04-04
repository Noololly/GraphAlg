//
// Created by olly on 16/09/2025.
//

#include "graph.h"
#include <ranges>
#include <algorithm>

graph::graph() = default;

void graph::addEdge(const int source, const int destination, const int weight) {
    edges.push_back({source, destination, weight});
    if (std::ranges::find(vertices, source) == vertices.end()) {
        vertices.push_back(source);
    }
    if (std::ranges::find(vertices, destination) == vertices.end()) {
        vertices.push_back(destination);
    }
}

void graph::addVertex(const int vertex) {
    if (std::ranges::find(vertices, vertex) == vertices.end()) {
        vertices.push_back(vertex);
    }
}

void graph::removeEdge(int source, int destination) {
    std::erase_if(edges,
                  [source, destination](const Edge& e) {
                      return (e.source == source && e.destination == destination) ||
                             (e.source == destination && e.destination == source);
                  });
}

void graph::removeVertex(int vertex) {
    std::erase(vertices, vertex);
    std::erase_if(edges,
                  [vertex](const Edge& e) {
                      return e.source == vertex || e.destination == vertex;
                  });
}

std::vector<Edge> graph::getNeighbours(const int source) const {
    std::vector<Edge> result;
    for (const auto& e : edges) {
        if (e.source == source) {
            result.push_back(e);
        }
    }
    return result;
}


int graph::size() const {
    return static_cast<int>(vertices.size());
}

std::vector<int> graph::getVertices() const {
    return vertices;
}
