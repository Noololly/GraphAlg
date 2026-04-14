//
// Created by olly on 13/04/2026.
//

#ifndef GRAPHALG_TEXT_WINDOW_H
#define GRAPHALG_TEXT_WINDOW_H
#include <vector>
#include "button.h"

enum class entryType {
    Start,
    End,
    Weight,
    Node
};
std::vector<Button> createAcceptCloseButtons();
int entryWindow(entryType entry);

#endif //GRAPHALG_TEXT_WINDOW_H
