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

void drawButtons(sf::RenderWindow& window, const std::vector<Button>& buttons, const sf::Font& font) {
    for (const auto& button : buttons) {
        sf::RectangleShape buttonRect({static_cast<float>(button.w), static_cast<float>(button.h)});
        buttonRect.setPosition({static_cast<float>(button.x), static_cast<float>(button.y)});
        buttonRect.setFillColor(sf::Color(203, 166, 247));
        window.draw(buttonRect);

        sf::Text label(font, button.text, 14);
        label.setFillColor(sf::Color::White);

        const sf::Vector2 labelRect = label.getLocalBounds().size;
        label.setOrigin({labelRect.x / 2, labelRect.y / 2});

        const sf::Vector2 buttonCentre = {buttonRect.getPosition().x + (buttonRect.getLocalBounds().size.x / 2), buttonRect.getPosition().y + (buttonRect.getLocalBounds().size.y / 2)};
        label.setPosition(buttonCentre);
        window.draw(label);
    }
}

void createButtons(std::vector<Button> &buttons) {
    int i = 0;
    for (const auto& coord : coords) {
        buttons.push_back(Button(coord.x, coord.y, 100, 80, labels[i]));
        i++;
    }
}
