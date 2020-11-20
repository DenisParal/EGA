#include "includes.h"

template<typename Container, typename Adaptation_func>
std::pair<typename Container::value_type, long int> BFS_Grey_algo(Container& using_field, const Adaptation_func& func, int N) {
    int position = rand() % using_field.size();
    std::pair<typename Container::value_type, long int> max(using_field[position], func(using_field[position]));
    std::pair<typename Container::value_type, long int> temp_pair=max;
    for (int i = 0; i < N; i++) {
        std::cout << "Current max data: ";
        print_pair(max);
        std::cout << "\n";
        Container neighbours = get_neighbours_on_grey(using_field,max.first);
        if(neighbours.size()==0){
            std::cout << "There are no neighbours\n";
            print_algo_result(max);
            std::cout <<"\n";
            return max;
        }
        std::cout << "***Neighbours list:\n";
        neighbours.print_all();
        std::cout << "******************\n";
        bool optimized = false;
        for (int i = 0; i < neighbours.size(); i++) {
            std::cout << "Current max data: ";
            print_pair(max);
            std::cout << " ";
            print_key(to_Grey(*(max.first)));
            std::cout << "\n";
            temp_pair.first=neighbours[i];
            temp_pair.second=func(neighbours[i]);
            std::cout << "Iteration data:   ";
            print_pair(temp_pair);
            std::cout << " ";
            print_key(to_Grey(*(temp_pair.first)));
            std::cout << "\n";
            if (temp_pair.second > max.second) {
                max = temp_pair;
                std::cout << "Optimized";
                std::cout << "\n\n";
                optimized = true;
                break;
            }
        }
        if(!optimized){
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