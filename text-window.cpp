//
// Created by olly on 13/04/2026.
//

#include "text-window.h"
#include<SFML/Graphics.hpp>

#include "Graph-ics.h"

std::vector<Button> createAcceptCloseButtons() {
    std::vector<Button> buttons;
    buttons.emplace_back(0, 20, 110, 100, 80, "Close");
    buttons.emplace_back(1, 140, 110, 100, 80, "OK");
    return buttons;
}

int entryWindow(const entryType entry) {
    sf::RenderWindow window(sf::VideoMode({260, 200}), "Text Entry");
    window.setFramerateLimit(60);
    sf::Font font;
    const bool hasFont = font.openFromFile("assets/NotoSans.ttf");

    const auto buttons = createAcceptCloseButtons();
    const Button* clickedButton = nullptr;

    sf::RectangleShape entryBox({180, 60});
    entryBox.setOrigin({entryBox.getLocalBounds().size.x / 2, entryBox.getLocalBounds().size.y / 2});
    entryBox.setPosition({40 + entryBox.getLocalBounds().size.x / 2, 40 + entryBox.getLocalBounds().size.y / 2});
    entryBox.setFillColor(sf::Color(224, 199, 255));

    std::string entryString;
    sf::Text entryText(font, entryString, 16);
    entryText.setFillColor(sf::Color::White);

    std::string keyword;
    switch (entry) {
        case entryType::Start:
            keyword = "start";
            break;
        case entryType::End:
            keyword = "end";
            break;
        case entryType::Weight:
            keyword = "weight";
            break;
        case entryType::Node:
            keyword = "";
            break;
    }

    const std::string instructionString = std::format("Enter {} node", keyword);
    sf::Text instructionText(font, instructionString, 16);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setOrigin({instructionText.getLocalBounds().size.x / 2, instructionText.getLocalBounds().size.y / 2});
    instructionText.setPosition({entryBox.getPosition().x, 25});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                return -1;
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                const auto code = keyPressed->code;

                const bool isNumber = code >= sf::Keyboard::Key::Num0 &&
                                code <= sf::Keyboard::Key::Num9;


                if (code == sf::Keyboard::Key::Backspace) {
                    if (!entryString.empty()) entryString.pop_back();
                } else if (isNumber){
                    const int digit = static_cast<int>(code) - static_cast<int>(sf::Keyboard::Key::Num0);
                    entryString.append(std::to_string(digit));
                } else {
                    break;
                }
                entryText.setString(entryString);
                entryText.setOrigin({entryText.getLocalBounds().size.x / 2, entryText.getLocalBounds().size.y / 2});
                entryText.setPosition(entryBox.getPosition());

            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const sf::Vector2i position = sf::Mouse::getPosition(window);

            for (auto& b : buttons) {
                if (b.x < position.x && position.x < (b.x + b.w)
                        && b.y < position.y && position.y < (b.y + b.h)) {
                    clickedButton = &b;
                    break;
                }
            }
        }

        if (clickedButton != nullptr) {
            if (clickedButton->id == 0) {
                return -1; // cancel pressed
            }
            if (clickedButton->id == 1) {
                if (!entryString.empty()) {
                    return std::stoi(entryString); // OK button pressed
                } else {
                    return -2;
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(instructionText);
        window.draw(entryBox);
        window.draw(entryText);
        window.draw(entryText);
        if (hasFont) drawButtons(window, buttons, font);

        window.display();
    }
    return 2;
}
