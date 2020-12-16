#include "includes.h"
#include "selections.hpp"

int main(){
    std::srand(std::time(nullptr));
    population<int> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return pow((convert(genotype,2)-pow(2,genotype.size()-1)),2);
    };
    for(long i=0;i<21;i++){
        pop.add(individual<int>(parse_func(i,2,5),adapt_func));
    }
    auto g=inbreeding_selection_strategy(std::size_t(2))(pop);
    for(auto x:g){
        print_key(x.first);
        std::cout <<" "<<x.first.adapt()<<" ";
        print_key(x.second);
        std::cout <<" "<<x.first.adapt()<<"\n";
    }
    std::cout <<"\n\n";
    
    auto r=positive_assotiative_selection_sterategy()(pop);
    for(auto x:r){
        print_key(x.first);
        std::cout <<" "<<x.first.adapt()<<" ";
        print_key(x.second);
        std::cout <<" "<<x.second.adapt()<<"\n";
    }
}