#include <iostream>
#include "Monte_Carlo_alg.h"
#include "DFS_alg.h"
#include "BFS_alg.h"
#include <cmath>

int main(){
    srand(time(0));
    int number_of_passes;
    int alg_number_of_passes;
    std::cout <<"Enter main loop length: ";
    std::cin >> number_of_passes;
    std::cout <<"Enter algorithms loop length: ";
    std::cin >> alg_number_of_passes;
    const long src_size=128;
    const long key_length=7;
    population<int> pop;
    
    auto adapt_func= [](const auto& genotype){
        return 5*sinl(convert(genotype,2))+logl(convert(genotype,2));
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,key_length),adapt_func));
    }
    for(int i=0;i<32;i++){
        print_key(*(pop.at(i)));
        std::cout <<" "<< pop.at(i)->adapt();
        std::cout <<"\n";
    }
    std::cout <<"\n\n";
    int decision;

    std::pair<std::shared_ptr<individual<int>>,long double> max(std::make_shared<individual<int>>(std::vector<int>{},[](const auto& genotype){
        return 0;
    }),0);
    std::pair<std::shared_ptr<individual<int>>,long double> tmp_max;

    for(int i=0;i<number_of_passes;i++){
        std::cout << "Current main max data: ";
        print_pair(max);
        std::cout <<"\n";
        decision=rand()%3;
        if(decision==0){
            std::cout <<"***Chosen method is monte_carlo algorithm***\n";
            tmp_max=MK_algo(pop,[](const std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    },alg_number_of_passes);
        }else if(decision==1){
            std::cout <<"***Chosen method is DFS***\n";
            tmp_max=DFS_algo(pop,[](const std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    },alg_number_of_passes);
        }else {
            std::cout <<"***Chosen method is BFS***\n";
            tmp_max=BFS_algo(pop,[](const std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    },alg_number_of_passes);
        }
        std::cout <<"Algorithm result:\n";
        if (tmp_max.second > max.second) {
            std::cout << "Optimum changed: ";
            print_pair(max);
            std::cout <<" -> ";
            print_pair(tmp_max);
            std::cout <<"\n";
            max = tmp_max;
        }else {
            std::cout <<"Optimum didn't change\n";
        }
        std::cout <<"\n\n";
    }
    std::cout <<"Out of attempts\nOptimum: ";
    print_pair(max);
    std::cout <<"\n";
}