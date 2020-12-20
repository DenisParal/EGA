#include "includes.h"
#include "reproductive_strategies.hpp"
#include "crossovers.hpp"
#include "mutations.hpp"
#include "selection_strategies.hpp"
#include "ending_conditions.hpp"

template<typename Crossover, typename Mutation, typename Reproduction, typename Selection, typename End_condition>
class algorithm_configuration{
public:
algorithm_configuration(const Crossover& cross_f, const Mutation& mut_f, const Reproduction& reprod_f, const Selection& select_f, const End_condition& e_cond):cross_f(cross_f),mut_f(mut_f),reprod_f(reprod_f),select_f(select_f),e_cond(e_cond) {}
template<typename T, typename Adapt_func> 
std::shared_ptr<individual<T>> operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const Adapt_func& func, long mutation_chance){
    long mutation_roll;
    int generation=1;
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> parents;
    std::vector<std::shared_ptr<individual<T>>> current_generation=population;
    std::vector<std::shared_ptr<individual<T>>> next_generation;
    std::shared_ptr<individual<T>> best_individ;
    do{
        parents=reprod_f(current_generation);
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
        current_generation=select_f(current_generation,next_generation);
        best_individ=current_generation[0];
        for(auto& x:current_generation){
            if(x->adapt()>best_individ->adapt()){
                best_individ=x;
            }
        }

        std::cout <<"\tGeneration number: "<<generation<<"\n";
        std::cout <<"Best individ: ";
        print_key(*best_individ);
        std::cout <<" ("<<best_individ->adapt()<<")\n";
        std::cout <<"Population:\n";
        for(std::size_t i=0;i<current_generation.size();i++){
            std::cout <<i+1<<") ";
            print_key(*(current_generation[i]));
            std::cout <<" ("<<current_generation[i]->adapt()<<")\n";
        }

        next_generation.clear();
    }while(e_cond(current_generation, best_individ));

    std::cout <<"\n\n\tFinal result: ";
    print_key(*best_individ);
    std::cout <<" ("<<best_individ->adapt()<<")\n";
    return best_individ;
}

End_condition e_cond;
Crossover cross_f;
Mutation mut_f;
Selection select_f;
Reproduction reprod_f;
};
