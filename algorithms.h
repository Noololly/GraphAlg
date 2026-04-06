//
// Created by olly on 06/04/2026.
//
#pragma once

#include <vector>
#include "graph.h"

#ifndef GRAPHALG_ALGORITHMS_H
#define GRAPHALG_ALGORITHMS_H

std::vector<int> dijkstra(const graph& g, int start, int end, int& distanceResult);
int depthUnvisitedNode(const graph& g, const std::vector<bool>& visited, int node);
std::vector<int> depthFirstSearch(const graph& g, int start);
std::vector<int> breadthFirstSearch(const graph& g, int start);
void algHelper(const graph& g, int alg);

#endif //GRAPHALG_ALGORITHMS_H
