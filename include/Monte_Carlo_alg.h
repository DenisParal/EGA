#pragma once
#include "includes.h"

template<typename T, typename Adaptation_func>
std::pair<genotype<T>, long int> MK_algo(population<T>& using_field, const Adaptation_func& func, int N) {
    std::pair<genotype<T>, long int> max(using_field[0], 0);
    std::pair<genotype<T>, long int> temp_pair(using_field[0],0);
    for (int i = 0; i < N; i++) {

        std::cout << "Current max data: ";
        print_pair(max);
        

        int position = rand() % using_field.size();
        temp_pair.first=using_field[position];
        temp_pair.second=func(temp_pair.first);
        
        std::cout << "Iteration data: ";
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