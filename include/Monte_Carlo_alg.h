#pragma once
#include "includes.h"

template<typename Container, typename Adaptation_func>
std::pair<typename Container::value_type, long int> MK_algo(Container& using_field, Adaptation_func&& func, int N) {
    int position = rand() % using_field.size();
    std::pair<typename Container::value_type, long int> max(using_field[position], func(using_field[position]));
    std::pair<typename Container::value_type, long int> temp_pair=max;
    for (int i = 0; i < N; i++) {

        std::cout << "Current max data: ";
        print_pair(max);
        std::cout <<"\n";
        
        position = rand() % using_field.size();
        temp_pair.first=using_field[position];
        temp_pair.second=func(temp_pair.first);
        
        std::cout << "Iteration data:   ";
        print_pair(temp_pair);

        if (temp_pair.second > max.second) {
            max = temp_pair;
            std::cout << "\nOptimized";
        }
        std::cout << "\n\n";
    }
    print_algo_result(max);
    std::cout <<"\n";
    return max;
}