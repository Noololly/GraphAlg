#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <cmath>
#include <sys/stat.h>

#include "SFML/Graphics.hpp"

#include "Graph-ics.h"
#include "graph.h"

#define RADIUS 20.f

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
    g.addEdge(1,3,10);
    g.addEdge(2,4,3);
    g.addEdge(3,4,1);
    //g.addEdge(4,5,4);

    sf::RenderWindow window(sf::VideoMode({H, W}), "GraphAlgs");
    window.setFramerateLimit(60);
    sf::Font font;
    const bool hasFont = font.openFromFile("assets/NotoSans.ttf");

    const std::vector<int> vertices = g.getVertices();
    std::vector<Node> nodes = convertNode(vertices, W, H);
    std::vector<Edge> edges = g.getEdges();

    bool simRunning = true;
    float repulsion = 8000.f;

    Node* draggedNode = nullptr;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    simRunning = !simRunning;
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                    window.clear();
                    nodes = {};
                    nodes = convertNode(vertices, W, H); // redraw the nodes
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const sf::Vector2i position = sf::Mouse::getPosition(window);

            if (draggedNode == nullptr) {
                for (auto& n : nodes) {
                    const float dx = static_cast<float>(position.x) - n.x;
                    const float dy = static_cast<float>(position.y) - n.y;
                    if (std::sqrt(dx * dx + dy * dy) <= RADIUS + 20) {
                        draggedNode = &n;
                        break;
                    }
                }
            }
            if (draggedNode != nullptr) {
                repulsion = 2000.f;
                draggedNode->x = static_cast<float>(position.x);
                draggedNode->y = static_cast<float>(position.y);
            }
        } else {
            draggedNode = nullptr;
            repulsion = 8000.f;
        }

        if (simRunning) applyForces(nodes, edges, repulsion, 0.03f, 150.f, 0.85f);

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
