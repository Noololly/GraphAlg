//
// Created by olly on 16/09/2025.
//

#ifndef DIJKSTRA2_GRAPH_H
#define DIJKSTRA2_GRAPH_H
#include <vector>
#include <unordered_map>

class graph {
public:
    graph();
    void addEdge(int source, int destination, int weight);
    void addVertex(int vertex);
    void removeEdge(int source, int destination);
    void removeVertex(int vertex);
    int size() const;
    void printGraph() const;
    std::vector<std::pair<int, int>> getNeighbours(int source) const;

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> m;

};

#endif //DIJKSTRA2_GRAPH_H