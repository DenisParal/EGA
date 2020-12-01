#pragma once
#include "includes.h"

template<typename Container, typename Adaptation_func>
std::pair<typename Container::value_type, long double> BFS_algo(Container& using_field, const Adaptation_func& func, int N) {
    int position = rand() % using_field.size();
    std::pair<typename Container::value_type, long double> max(using_field[position], func(using_field[position]));
    std::pair<typename Container::value_type, long double> temp_pair=max;
    for (int i = 0; i < N; i++) {
        std::cout <<"***** STEP "<<i<<" *****\n";
        std::cout << "Current max data: ";
        print_pair(max);
        std::cout << "\n";

        Container neighbours = get_neighbours(using_field,max.first);

        if(neighbours.size()==0){
            std::cout << "There are no neighbours\n";
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }

        std::cout << "***Neighbours list:\n";
        neighbours.print_all();
        std::cout << "******************\n";

        int opt_i=optimum(neighbours,[&func](const typename Container::value_type& first, const typename Container::value_type& second){
            return func(first)>func(second);
        });

        temp_pair.first=neighbours[opt_i];
        temp_pair.second=func(neighbours[opt_i]);

        std::cout << "Iteration data:   ";
        print_pair(temp_pair);
        std::cout << "\n";

        if (temp_pair.second > max.second) {
            max = temp_pair;
            std::cout << "Optimized";
            std::cout << "\n\n";
        }else{
            std::cout << "There are no better individuals in neighbours\n";
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }
    }
    std::cout << "Out of attempts\n";
    print_algo_result(max);
    std::cout << "\n";
    return max;
}