//
// Created by olly on 06/04/2026.
//

#include "algorithms.h"

#include <algorithm>
#include <climits>
#include <map>
#include <ranges>
#include <sstream>

#include "oPQueue.h"
#include "oQueue.h"
#include "oStack.h"
#include "text-window.h"

std::string algHelper(const graph& graph, const Algorithm algorithm) {
    /* This is a nice function that stops my code from repeating as much. */
    const int start = entryWindow(entryType::Start);
    if (!start) {
        return "";
    }
    std::ostringstream out;
    if (algorithm == Dijkstra) {
        const int end = entryWindow(entryType::End);
        int distanceResult;
        const std::vector<int> path = dijkstra(graph, start, end, distanceResult);
        if (path.empty() || distanceResult == INT_MAX) {
            out << "No path found.";
        } else {
            for (size_t i = 0; i < path.size(); i++) {
                out << path[i];
                if (i + 1 < path.size()) out << " -> ";
            }
            out << "\nDistance: " << distanceResult;
        }
    } else if (algorithm == BFS || algorithm == DFS) {
        const std::vector<int> path = algorithm == DFS ? depthFirstSearch(graph, start) : breadthFirstSearch(graph, start) ;
        for (size_t i = 0; i < path.size(); i++) {
            out << path[i];
            if (i + 1 < path.size()) out << " -> ";
        }
    }
    return out.str();
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
    std::vector<int> unvisited = g.getVertices();
    std::map<int, int> dist;
    std::map<int, int> prev;

    for (int v : unvisited) {
        dist[v] = INT_MAX;
    }
    dist[start] = 0;

    while (!unvisited.empty()) {
        // pick the unvisited vertex with smallest distance
        int vertex = unvisited[0];
        for (int v : unvisited) {
            if (dist[v] < dist[vertex]) vertex = v;
        }
        if (dist[vertex] == INT_MAX) break;

        for (const auto& edge : g.getNeighbours(vertex)) {
            int neighbour = edge.destination;
            const int weight = edge.weight;
            if (std::ranges::find(unvisited, neighbour) == unvisited.end()) {
                continue;
            }
            if (const int newDist = dist[vertex] + weight; newDist < dist[neighbour]) {
                dist[neighbour] = newDist;
                prev[neighbour] = vertex;
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
        return -1;
    } else {
        for (const auto& edge : children) {
            if (const int child = edge.destination; !visited[child]) {
                return child;
            }
        }
    }
    return -1;
}