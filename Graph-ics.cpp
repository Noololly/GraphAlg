//
// Created by olly on 03/04/2026.
//

#include <random>

#include "Graph-ics.h"


#define RADIUS 20.f;

std::vector<Node> convertNode(const std::vector<int>& vertices, const u_int dx, const u_int dy) {
    std::vector<Node> nodes;
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> rx(0, static_cast<float>(dx));
    std::uniform_real_distribution<float> ry(0, static_cast<float>(dy));
    for (const int vertex : vertices) {
        nodes.push_back(Node(rx(rng), ry(rng), 0, 0, vertex));
    }

    return nodes;
}

void applyForces(std::vector<Node>& nodes, const std::vector<Edge>& edges, const float repulsion,
    const float springK, const float springLenMultiplier, const float damping) {
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            const float dx = nodes[j].x - nodes[i].x;
            const float dy = nodes[j].y - nodes[i].y;
            const float dist = std::sqrt(dx*dx + dy*dy);
            const float force = repulsion / (dist*dist);
            nodes[i].vx -= force * dx / dist;
            nodes[i].vy -= force * dy / dist;
            nodes[j].vx += force * dx / dist;
            nodes[j].vy += force * dy / dist;
        }
    }

    for (auto& e : edges) {
        const float dx = nodes[e.destination].x - nodes[e.source].x;
        const float dy = nodes[e.destination].y - nodes[e.source].y;
        const float dist = std::sqrt(dx*dx + dy*dy);
        const float force = springK * (dist - springLenMultiplier);
        nodes[e.source].vx += force * dx / dist;
        nodes[e.source].vy += force * dy / dist;
        nodes[e.destination].vx -= force * dx / dist;
        nodes[e.destination].vy -= force * dy / dist;
    }

    for (auto& n : nodes) {
        n.x += n.vx;
        n.y += n.vy;
        n.vx *= damping;
        n.vy *= damping;
    }
}
