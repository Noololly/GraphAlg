#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Graph-ics.h"

#include "graph.h"
#include "oPQueue.h"
#include "oStack.h"

#define RADIUS 20.f

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

void printMenu() {
    printf("\n1. Add vertex to graph\n"
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
    constexpr int W = 600, H = 600;
    printf("  ____                 _        _    _           \n"
           " / ___|_ __ __ _ _ __ | |__    / \\  | | __ _ ___ \n"
           "| |  _| '__/ _` | '_ \\| '_ \\  / _ \\ | |/ _` / __|\n"
           "| |_| | | | (_| | |_) | | | |/ ___ \\| | (_| \\__ \\ \n"
           " \\____|_|  \\__,_| .__/|_| |_/_/   \\_\\_|\\__, |___/\n"
           "               |_|                    |___/     \n");
    graph g;

    for (int i = 0; i <= 5; i++) {
        g.addVertex(i);
    }

    g.addEdge(0,1,4);
    g.addEdge(0,2,2);
    g.addEdge(1,2,5);
    //g.addEdge(1,3,10);
    g.addEdge(2,4,3);
    g.addEdge(3,4,1);
    g.addEdge(4,5,4);

    sf::RenderWindow window(sf::VideoMode({H, W}), "GraphAlgs");
    window.setFramerateLimit(60);
    sf::Font font;
    const bool hasFont = font.openFromFile("assets/NotoSans.ttf");

    const std::vector<int> vertices = g.getVertices();
    std::vector<Node> nodes = convertNode(vertices, window.getSize().x, window.getSize().y);
    std::vector<Edge> edges = g.getEdges();

    bool simRunning = true;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    simRunning = !simRunning;
                }
            }
        }

        if (simRunning) applyForces(nodes, edges, 8000.f, 0.03f, 150.f, 0.85f);

        for (auto& n : nodes) {
            n.x = std::clamp(n.x, RADIUS, W - RADIUS);
            n.y = std::clamp(n.y, RADIUS, H - RADIUS);
        }

        window.clear(sf::Color(30, 30, 30));

        for (const auto&[source, destination, weight] : edges) {
            const sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(nodes[source].x, nodes[source].y), sf::Color(150,150,150)),
                sf::Vertex(sf::Vector2f(nodes[destination].x, nodes[destination].y), sf::Color(150,150,150))
            };
            window.draw(line, 2, sf::PrimitiveType::Lines);

            if (hasFont) {
                float mx = (nodes[source].x + nodes[destination].x) / 2;
                float my = (nodes[source].y + nodes[destination].y) / 2;
                sf::Text wt(font, std::to_string(weight), 14);
                wt.setFillColor(sf::Color::Magenta);
                wt.setPosition({mx, my});
                window.draw(wt);
            }
        }

        for (auto& n : nodes) {
            sf::CircleShape circle (RADIUS);
            circle.setFillColor(sf::Color(85, 0, 130));
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(2.f);
            circle.setOrigin({RADIUS, RADIUS});
            circle.setPosition({n.x, n.y});
            window.draw(circle);

            if (hasFont) {
                sf::Text label(font, std::to_string(n.id), 16);
                label.setFillColor(sf::Color::White);
                const sf::Vector2 labelRect = label.getLocalBounds().size;

                label.setOrigin({labelRect.x / 2, labelRect.y / 2});
                label.setPosition({n.x - 1, n.y - 4});
                window.draw(label);
            }
        }



        window.display();
    }

    return 0;
}
