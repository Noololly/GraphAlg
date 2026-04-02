#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>
#include <string>

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

void dijkstra_helper(const graph& g) {
    int start, end;
    printf("Start: ");
    std::cin >> start;
    printf("End: ");
    std::cin >> end;
    const std::vector<int> path = dijkstra(g, start, end);
    for (size_t i = 0; i < path.size(); i++) {
        printf("%d", path[i]);
        if (i + 1 < path.size()) printf(" -> ");
    }
    printf("\n");
}

int depthUnvisitedNode(const graph& g, const std::vector<int>& visited, const int node) {
    if (const auto children = g.getNeighbours(node); children.empty()) {
        return 0;
    } else {
        for (const auto &child: children | std::views::keys) {
            if (!visited[child]) {
                return child;
            }
        }
    }
    return -1;
}

std::string depthFirstSearch(const graph& g, const int start) {
    const int graphSize = g.size();
    std::vector<int> visited;
    oStack<int> stack;
    oQueue<int> queue(graphSize);
    std::string path;
    for (int i = 1; i <= graphSize; i++) {
        visited[i] = false;
    }

    path.append(std::to_string(start));
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
            path.append(std::to_string(nextNode) + " -> ");
        }
    }
    return path;
}

void printMenu() {
    printf("1. Add vertex to graph\n"
           "2. Add edge\n"
           "3. Remove vertex\n"
           "4. Remove edge\n"
           "5. Print graph\n"
           "6. Dijkstra\n"
           "7. DFS\n"
           "8. BFS\n"
           "9. Exit\n");
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
    g.addEdge(14,5,1);

    bool running = true;
    while (running) {
        printMenu();
        int input;
        std::cin >> input;
        int start, end, weight, vertex;
        switch (input) {
            default:
                break;
            case 1: // add vertex
                printf("Vertex number: ");
                std::cin >> vertex;
                g.addVertex(vertex);
                break;
            case 2: // add edge
                printf("Enter start vertex: ");
                std::cin >> start;
                printf("Enter end vertex: ");
                std::cin >> end;
                printf("Enter weight: ");
                std::cin >> weight;
                g.addEdge(start, end, weight);
                break;
            case 3: // remove edge
                printf("Enter start vertex: ");
                std::cin >> start;
                printf("Enter end vertex: ");
                std::cin >> end;
                g.removeEdge(start, end);
                break;

            case 4: // remove vertex
                printf("Enter vertex to remove: ");
                std::cin >> vertex;
                g.removeVertex(vertex);
                break;

            case 5:
                g.printGraph();
                break;

            case 6:
                dijkstra_helper(g);
                break;

            case 7:
                std::cout << depthFirstSearch(g, 1);
                break;

            case 9:
                running = false;
                break;
        }
    }

    return 0;
}