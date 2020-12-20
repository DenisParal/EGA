#include "includes.h"
#include "selections.hpp"
#include "crossovers.hpp"

int main(){
    std::srand(std::time(nullptr));
    population<int> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return pow((convert(genotype,2)-pow(2,genotype.size()-1)),2);
    };
    for(long i=0;i<64;i++){
        pop.add(individual<int>(parse_func(i,2,6),adapt_func));
    }
//     auto g=inbreeding_selection_strategy(std::size_t(2))(pop);
//     for(auto x:g){
//         print_key(*(x.first));
//         std::cout <<" "<<x.first->adapt()<<" ";
//         print_key(*(x.second));
//         std::cout <<" "<<x.second->adapt()<<"\n";
//     }
//     std::cout <<"\n\n";
    
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

    std::pair<std::shared_ptr<individual<int>>,std::shared_ptr<individual<int>>> pair(pop[0],pop[63]);
    print_key(*(pair.first));
    std::cout <<"\n";
    print_key(*(pair.second));
    std::cout <<"\n\n\n";
    auto res=homogen_equal_crossover()(pair,2,adapt_func);
    print_key(*(res[0]));
    std::cout <<"\n";
    print_key(*(res[1]));

}