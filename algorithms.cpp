//
// Created by olly on 06/04/2026.
//

#include "algorithms.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ranges>

#include "oPQueue.h"
#include "oQueue.h"
#include "oStack.h"

void algHelper(const graph& g, const int alg) {
    /* This is a nice function that stops my code from repeating as much.
     * Alg corresponds to:
     * 0: Dijkstra
     * 1: DFS
     * 2: BFS
     */
    int start;
    printf("Start: ");
    std::cin >> start;
    if (alg == 0) {
        int end;
        printf("End: ");
        std::cin >> end;
        int distanceResult;
        const std::vector<int> path = dijkstra(g, start, end, distanceResult);
        for (size_t i = 0; i < path.size(); i++) {
            printf("%d", path[i]);
            if (i + 1 < path.size()) printf(" -> ");
        }
        printf("\n");
        printf("Distance: %d", distanceResult);
    } else if (alg == 1 || alg == 2) {
        const std::vector<int> path = alg == 1 ? depthFirstSearch(g, start) : breadthFirstSearch(g, start) ;
        for (size_t i = 0; i < path.size(); i++) {
            printf("%d", path[i]);
            if (i + 1 < path.size()) printf(" -> ");
        }
        printf("\n");

    }
}

std::vector<int> breadthFirstSearch(const graph& g, const int start) {
    const int graphSize = g.size();
    std::vector visited(graphSize, false);
    std::vector<int> path;
    oQueue<int> queue(graphSize);
    visited[start] = true;
    path.push_back(start);
    queue.push(start);

    while (!queue.isEmpty()) {
        for (const int nextNode = queue.pop(); const auto& edge : g.getNeighbours(nextNode)) {
            if (int neighbour = edge.destination; !visited[neighbour]) {
                visited[neighbour] = true;
                queue.push(neighbour);
                path.push_back(neighbour);
            }
        }
    }
    return path;
}

std::vector<int> depthFirstSearch(const graph& g, const int start) {
    const int graphSize = g.size();
    std::vector visited(graphSize, false);
    oStack<int> stack;
    std::vector<int> path;

    path.push_back(start);
    visited[start] = true;
    stack.push(start);

    int nextNode = start;
    while (!stack.isEmpty()) {
        nextNode = depthUnvisitedNode(g, visited, nextNode);
        if (nextNode == -1) {
            stack.pop();
            if (!stack.isEmpty()) {
                nextNode = stack.peek();
            } else break;
        } else {
            stack.push(nextNode);
            visited[nextNode] = true;
            path.push_back(nextNode);
        }
    }
    return path;
}

std::vector<int> dijkstra(const graph& g, const int start, const int end, int& distanceResult) {
    const int gSize = g.size();
    std::vector<int> unvisited;
    std::map<int, int> dist;
    std::map<int, int> prev;

    for (int i = 0; i <= gSize; i++) {
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
        for (const auto& edge : g.getNeighbours(vertex)) {
            int neighbour = edge.destination;
            const int weight = edge.weight;
            if (std::ranges::find(unvisited, neighbour) == unvisited.end()) {
                continue;
            }
            if (dist[vertex] != INT_MAX) {
                if (const int newDist = dist[vertex] + weight; newDist < dist[neighbour]) {
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
    distanceResult = dist[end];
    return path;
}

int depthUnvisitedNode(const graph& g, const std::vector<bool>& visited, const int node) {
    if (const auto children = g.getNeighbours(node); children.empty()) {
        return 0;
    } else {
        for (const auto& edge : children) {
            if (const int child = edge.destination; !visited[child]) {
                return child;
            }
        }
    }
    return -1;
}