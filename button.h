//
// Created by olly on 13/04/2026.
//

#ifndef GRAPHALG_BUTTON_H
#define GRAPHALG_BUTTON_H

#include <SFML/Graphics.hpp>

struct Button {
    int id, x, y, w, h;
    sf::String text;
    Button(const int id, const int x, const int y, const int w, const int h, sf::String  text) : id(id), x(x), y(y), w(w), h(h), text(std::move(text)){}
};

#endif //GRAPHALG_BUTTON_H
