#include "includes.h"
#include "selections.hpp"
#include "crossovers.hpp"
#include "mutations.hpp"
#include "ending_conditions.hpp"

template<typename Crossover, typename Mutation, typename Selection, typename End_condition>
class algorithm_configuration{
public:
algorithm_configuration(const Crossover& cross_f, const Mutation& mut_f, const Selection& sel_f, const End_condition& e_cond):cross_f(cross_f),mut_f(mut_f),sel_f(sel_f),e_cond(e_cond) {}
template<typename T, template Adapt_func> 
std::shared_ptr<individual<T>> operator()(const population<T>& population, const Adapt_func& func, long mutation_chance){
    long mutation_roll;
    int generation=1;
    std::vector<std::shared_ptr<individual<T>>> parents;
    std::vector<std::shared_ptr<individual<T>>> current_generation=population;
    std::vector<std::shared_ptr<individual<T>>> next_generation;
    std::shared_ptr<individual<T>> best_individ;
    do{
        parents=sel_f(current_generation);
        for(auto& pair:parents){
        auto offspring=cross_f(pair,func);
        for(auto& individ:offspring){
            mutation_roll=rand()%101;
            if(mutation_roll<=mutation_chance){
                mut_f(individ);
            }
            next_generation.push_back(individ);
        }
    }
    ++generation;
    current_generation=next_generation;
    best_individ=std::max(current_generation.begin(),current_generation.end(),[](auto& individ1, auto& individ2){
        return individ1->adaptation_value>individ2->adaptation_value;
    });

    std::cout <<"\tGeneration number: "<<generation<<"\n";
    std::cout <<"Best individ: ";
    print_key(*best_individ);
    std::cout <<" ("<<best_individ->adaptation_value<<")\n";
    std::cout <<"Population:\n";
    for(std::size_t i=0;i<current_generation.size();i++){
        std::cout <<i+1<<") ";
        print_key(*(current_generation[i]));
        std::cout <<" ("<<current_generation[i]->adaptation_value<<")\n";
    }

    next_generation.clear();
    }while(e_cond(current_generation, best_individ));
    std::cout <<"\n\n\tFinal result: ";
    print_key(*best_individ);
    std::cout <<" ("<<best_individ->adaptation_value<<")\n";
    return best_individ;
}

End_condition e_cond;
Crossover cross_f;
Mutation mut_f;
Selection sel_f;
};
