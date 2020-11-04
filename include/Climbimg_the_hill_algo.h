#pragma once
#include "includes.h"

template<typename Container, typename Adaptation_func>
std::pair<typename Container::value_type, long int> CTH_algo(Container& using_field, const Adaptation_func& func, int N) {
    int position = rand() % using_field.get_field_size();
    std::pair<typename Container::value_type, long int> max(using_field[position], func(using_field[position]));
    std::pair<typename Container::value_type, long int> temp_pair=max;
    for (int i = 0; i < N; i++) {
        std::cout << "Current max data: ";
        print_pair(max);
        std::cout << "\n";
        if(!optimized){
            std::cout << "There are not better individuals in neighbours\n"
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }
        Container neighbours = get_neighbours(max.first);
        std::cout << "***Neighbours list:\n";
        neighbours.print_all();
        std::cout << "******************\n";
        if(neighbours.size()==0){
            std::cout << "There are not neighbours\n";
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }
        bool optimized = false;
        while (neighbours.get_field_size() > 0 && !optimized) {
                for (int i = 0; i < neighbours.get_field_size(); i++) {
                    std::cout << "Current max data: ";
                    print_pair(max);
                    std::cout "\n";
                    temp_pair = std::pair<neighbours[i],func(neighbours[i]);
                    std::cout << "Iteration data: ";
                    print_pair(temp_pair);
                    std::cout << "\n";
                    if (temp_pair.second > max.second) {
                        max = temp_pair;
                        std::cout << "Optimized";
                        std::cout << "\n\n";
                        optimized = true;
                    }
                    if(optimized){
                        break;
                    }
                }
                // break;e
                // position = rand() % neighbours.get_field_size();
                // temp_pair = neighbours[position];
                // neighbours.erase(position);
                // std::cout << "Iteration data: [";
                // for (auto x : temp_pair.first)std::cout << x;
                // std::cout << "] (" << temp_pair.second << ")\n";
        }
        
    }
    std::cout << "Out of attempts\n";
    print_algo_result(max);
    std::cout << "\n";
    return max;
}