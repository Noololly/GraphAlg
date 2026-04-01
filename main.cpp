#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include "graph.h"
#include "oPQueue.h"
#include "oStack.h"

std::vector<int> dijkstra(const graph& g, const int start, const int end) {
    const int gSize = g.size();
    std::vector<int> unvisited;
    std::map<int, int> dist;
    std::map<int, int> prev;

    for (int i = 1; i <= gSize; i++) {
        unvisited.push_back(i);
        dist[i] = INT_MAX; // big number

    }

    dist[start] = 0;

    oPQueue<int> q(gSize);
    for (auto vertex : unvisited) {
        q.push(vertex);
    }

    while (!q.isEmpty()) {
        int vertex = q.pop();
        for (auto [neighbour, weight] : g.getNeighbours((vertex))) {
            if (std::ranges::find(unvisited, neighbour) == unvisited.end()) {
                continue;
            }
            if (dist[vertex] != INT_MAX) {
                int newDist = dist[vertex] + weight;
                if (newDist < dist[neighbour]) {
                    dist[neighbour] = newDist;
                    prev[neighbour] = vertex;
                }
            }
        }
        unvisited.erase(std::ranges::remove(unvisited, vertex).begin(), unvisited.end());
    }
    std::vector<int> path;
    int cur = end;
    while (prev.contains(cur)) {
        path.push_back(cur);
        cur = prev[cur];
    }
    if (cur == start) path.push_back(start);
    std::ranges::reverse(path);
    return path;
}

int main() {
    graph g;

    for (int i = 1; i <= 5; i++) {
        g.addVertex(i);
    }

    g.addEdge(1,2,4);
    g.addEdge(1,3,2);
    g.addEdge(2,3,5);
    g.addEdge(2,4,10);
    g.addEdge(3,5,3);
    g.addEdge(4,5,1);

    //g.printGraph();

    std::vector<int> path = dijkstra(g, 1, 5);
    for (size_t i = 0; i < path.size(); i++) {
        printf("%d", path[i]);
        if (i + 1 < path.size()) printf(" -> ");
    }
    printf("\n");

    return 0;
}