//
// Created by olly on 03/04/2026.
//

#ifndef GRAPHALG_GRAPH_ICS_H
#define GRAPHALG_GRAPH_ICS_H

#include "graph.h"
#include <SFML/Graphics.hpp>

struct Node {
    float x,y, vx, vy;
    int id;
};

struct Button {
    int x, y, w, h;
    sf::String text;
    Button(const int x, const int y, const int w, const int h, const sf::String& text) : x(x), y(y), w(w), h(h), text(text){}
};

inline std::vector<sf::Vector2i> coords = {
    {25, 610}, {175, 610}, {325, 610}, {475, 610},
    {25, 710}, {175, 710}, {325, 710}, {475, 710}
};
inline std::vector<sf::String> labels = {"Add Edge", "Add Node", "Remove Edge", "Remove Node",
    "Dijkstra", "Breadth\nFirst\nSearch", "Depth\nFirst\nSearch", "Exit"};

std::vector<Node> convertNode(const std::vector<int>& vertices, u_int dx, u_int dy);
void applyForces(std::vector<Node>& nodes, const std::vector<Edge>& edges, float repulsion,
    float springK, float springLenMultiplier, float damping);
void createButtons(std::vector<Button>& buttons);
void drawButtons(sf::RenderWindow& window, const std::vector<Button>& buttons, const sf::Font& font);

#endif //GRAPHALG_GRAPH_ICS_H
