#include "includes.h"
#include "genetic_algorithm.hpp"

int main(){
    std::srand(std::time(nullptr));
    std::vector<std::shared_ptr<individual<int>>> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return pow((convert(genotype,2)-pow(2,genotype.size()-1)),2);
    };
    for(long i=0;i<32;i++){
        pop.push_back(std::make_shared<individual<int>>(parse_func(i,2,6),adapt_func));
    }
    auto g=inbreeding_reproductive_strategy(std::size_t(2))(pop);
    // for(auto x:g){
    //     print_key(*(x.first));
    //     std::cout <<" "<<x.first->adapt()<<" ";
    //     print_key(*(x.second));
    //     std::cout <<" "<<x.second->adapt()<<"\n";
    // }
    std::cout <<"\n\n";
    
//     auto r=positive_assotiative_selection_sterategy()(pop);
//    for(auto x:g){
//         print_key(*(x.first));
//         std::cout <<" "<<x.first->adapt()<<" ";
//         print_key(*(x.second));
//         std::cout <<" "<<x.second->adapt()<<"\n";
//     }
//     std::cout <<"\n\n";
    
//     auto r1=negative_assotiative_selection_sterategy()(pop);
//     for(auto x:g){
//         print_key(*(x.first));
//         std::cout <<" "<<x.first->adapt()<<" ";
//         print_key(*(x.second));
//         std::cout <<" "<<x.second->adapt()<<"\n";
//     }
        // std::vector<std::shared_ptr<individual<int>>> next_generation;
        // long mutation_chance=20;
        // long mutation_roll;
        // for(auto& pair:g){
        // auto offspring=homogen_equal_crossover()(pair,adapt_func);
        // for(auto& individ:offspring){
        //     mutation_roll=rand()%101;
        //     if(mutation_roll<=mutation_chance){
        //         point_mut(individ);
        //     }
        //     next_generation.push_back(individ);
        // }
        // }

        // auto result=stable_select_strategy(30)(pop,next_generation);

    // std::pair<std::shared_ptr<individual<int>>,std::shared_ptr<individual<int>>> pair(pop[0],pop[63]);
    // print_key(*(pair.first));
    // std::cout <<"\n";
    // print_key(*(pair.second));
    // std::cout <<"\n\n\n";
    // auto res=homogen_equal_crossover()(pair,2,adapt_func);
    // print_key(*(res[0]));
    // std::cout <<"\n";
    // print_key(*(res[1]));


    auto sel=stable_select_strategy(50);
    auto mut=point_mut();
    auto reprod=positive_assotiative_reproductive_sterategy();
    auto cross=homogen_equal_crossover();
    auto e_cond=max_generation_cond(10);

    auto algorithm=algorithm_configuration<homogen_equal_crossover,point_mut,positive_assotiative_reproductive_sterategy,stable_select_strategy,max_generation_cond>(
        cross,mut,reprod,sel,e_cond
    );
    algorithm(pop,adapt_func,20);



}