//
// Created by olly on 16/09/2025.
//

#ifndef DIJKSTRA2_GRAPH_H
#define DIJKSTRA2_GRAPH_H

#include <vector>

struct Edge {
    int source;
    int destination;
    int weight;
};

class graph {
public:
    graph();
    void addEdge(int source, int destination, int weight);
    void addVertex(int vertex);
    void removeEdge(int source, int destination);
    void removeVertex(int vertex);
    [[nodiscard]] int size() const;
    [[nodiscard]] std::vector<int> getVertices() const;
    [[nodiscard]] std::vector<Edge> getNeighbours(int source) const;
    [[nodiscard]] std::vector<Edge> getEdges() const { return edges; }

private:
    std::vector<Edge> edges;
    std::vector<int> vertices;
};

#endif //DIJKSTRA2_GRAPH_H