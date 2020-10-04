#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Field.h"

template<typename Iterator>
void reverse(Iterator& begin, Iterator& end) {
    while (end - begin > 2) {
        std::swap(*begin, *end);
        ++begin;
        --end;
    }
}
void print_pair(std::pair<std::vector<int>, long int> pair) {
    std::cout << "[";
    for (auto x : pair.first)std::cout << x;
    std::cout << "] (" << pair.second << ")\n";
}
std::pair<std::vector<int>, long int> MK_algo(field& using_field, int N) {
    std::pair<std::vector<int>, long int> max({}, 0);
    std::pair<std::vector<int>, long int> temp_pair;
    for (int i = 0; i < N; i++) {

        std::cout << "Current max data: ";
        print_pair(max);
        

        int position = rand() % using_field.get_field_size();
        temp_pair = using_field[position];
        
        std::cout << "Iteration data: ";
        print_pair(temp_pair);

        if (temp_pair.second > max.second) {
            max = temp_pair;
            std::cout << "\nOptimizes";
        }
        std::cout << "\n\n";
    }
    std::cout << "*****Algorithm result: pair<";
    for (auto x : max.first)std::cout << x;
    std::cout <<">*****\n";
    return max;
}


std::pair<std::vector<int>, long int> CTH_algo(field& using_field, int N, bool widht=false) {
    int position = rand() % using_field.get_field_size();
    std::pair<std::vector<int>, long int> max(using_field[position].first, using_field[position].second);
    std::pair<std::vector<int>, long int> temp_pair;
    for (int i = 0; i < N; i++) {
        std::cout << "Current max data: [";
        for (auto x : max.first)std::cout << x;
        std::cout << "] (" << max.second << ")\n";

        field neighbours = using_field.get_neighbours(max.first);
        std::cout << "***Neighbours list:\n";
        neighbours.print_field();
        std::cout << "******************\n";
        bool optimized = false;
        while (neighbours.get_field_size() > 0) {
            if (widht) {
                for (int i = 0; i < neighbours.get_field_size(); i++) {
                    std::cout << "Current max data: [";
                    for (auto x : max.first)std::cout << x;
                    std::cout << "] (" << max.second << ")\n";
                    temp_pair = neighbours[i];
                    std::cout << "Iteration data: [";
                    for (auto x : temp_pair.first)std::cout << x;
                    std::cout << "] (" << temp_pair.second << ")\n";
                    if (temp_pair.second > max.second) {
                        max = temp_pair;
                        std::cout << "Optimized";
                        std::cout << "\n\n";
                        optimized = true;
                    }
                }
                break;
            }
            else {
                position = rand() % neighbours.get_field_size();
                temp_pair = neighbours[position];
                neighbours.erase(position);
                std::cout << "Iteration data: [";
                for (auto x : temp_pair.first)std::cout << x;
                std::cout << "] (" << temp_pair.second << ")\n";

                if (temp_pair.second > max.second) {
                    max = temp_pair;
                    std::cout << "Optimized";
                    std::cout << "\n\n";
                    break;
                }
            }
        }
        if (!widht&&neighbours.get_field_size() > 0||widht&&optimized) {
            continue;
        }
        std::cout << "Out of neibhours\n";
        std::cout << "*****Algorithm result: pair<[";
        for (auto x : max.first)std::cout << x;
        std::cout << "] (" << max.second << ")>*****\n";
        return max;
    }
    std::cout << "Out of attempts\n";
    std::cout << "*****Algorithm result: pair<[";
    for (auto x : max.first)std::cout << x;
    std::cout << "] (" << max.second << ")>*****\n";
    return max;
}