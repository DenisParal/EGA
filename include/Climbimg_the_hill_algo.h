#pragma once
#include "includes.h"

template<typename T, typename Adaptation_func, bool is_width_search=false>
std::pair<std::vector<int>, long int> CTH_algo(population<T>& using_field, const Adaptation_func& func, int N) {
    int position = rand() % using_field.get_field_size();
    std::pair<std::vector<int>, long int> max(using_field[position].first, using_field[position].second);
    std::pair<std::vector<int>, long int> temp_pair;
    for (int i = 0; i < N; i++) {
        std::cout << "Current max data: ";
        print_elem(max);
        std::cout << "\n";

        population<T> neighbours = using_field.get_neighbours(max.first);
        std::cout << "***Neighbours list:\n";
        neighbours.print_field();
        std::cout << "******************\n";
        bool optimized = false;
        while (neighbours.get_field_size() > 0) {
            if constexpr(is_width_search) {
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
        if (!is_width_search&&neighbours.get_field_size() > 0||is_width_search&&optimized) {
            continue;
        }
        
    }
    std::cout << "Out of attempts\n";
    print_algo_result(max);
    std::cout << "\n";
    return max;
}