#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "utils.h"
#include "Genetic.h"

population<int> get_neighbours(const population<int>& popul, const genotype<int>& key) {
    population<int> result;
    for (int i = 0; i < popul.size(); i++) {
        if (get_distance(key, popul[i]) == 1) {
            result.add(popul[i]);
        }
    }
    return result;
}

void print_elem(const std::pair<std::vector<int>, long int>& pair) {
    std::cout << "<[";
    for (auto x : pair.first) {
        std::cout << x;
    }
    std::cout << "] (" << pair.second << ")> ";
}
