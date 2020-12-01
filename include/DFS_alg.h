#pragma once
#include "includes.h"

template<typename Container, typename Adaptation_func>
std::pair<typename Container::value_type, long double> DFS_algo(Container& using_field, const Adaptation_func& func, int N) {
    int position = rand() % using_field.size();
    std::pair<typename Container::value_type, long double> max(using_field[position], func(using_field[position]));
    std::pair<typename Container::value_type, long double> temp_pair=max;
    Container neighbours = get_neighbours(using_field,max.first);
    for (int i = 0; i < N; i++) {
        std::cout <<"***** STEP "<<i<<" *****\n";
        std::cout << "Current max data: ";
        print_pair(max);
        std::cout << "\n";
        if(neighbours.size()==0){
            std::cout << "There are not candidats\n";
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }
        std::cout << "***Neighbours list:\n";
        neighbours.print_all();
        std::cout << "******************\n";

        position = rand() % neighbours.size();
        temp_pair.first=neighbours[position];
        temp_pair.second=func(neighbours[position]);

        neighbours.erase(position);

        std::cout << "Iteration data:   ";
        print_pair(temp_pair);
        std::cout <<"\n";

        if (temp_pair.second > max.second) {
            max = temp_pair;
            std::cout << "Optimized";
            std::cout << "\n\n";
            neighbours = get_neighbours(using_field,max.first);
            continue;
        }
    }
    std::cout << "Out of attempts\n";
    print_algo_result(max);
    std::cout << "\n";
    return max;
}