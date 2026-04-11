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
};


std::vector<Node> convertNode(const std::vector<int>& vertices, u_int dx, u_int dy);
void applyForces(std::vector<Node>& nodes, const std::vector<Edge>& edges, float repulsion,
    float springK, float springLenMultiplier, float damping);
void drawButtons(sf::Window& window);

#endif //GRAPHALG_GRAPH_ICS_H
