#include "genetic_algorithm.hpp"
#include <fstream>

std::ifstream fin;

template<typename Adaptation_func, typename Comparator>
class menu{
public:
menu(const std::vector<selection_strategy<int,Decider>*>& sel_str, const std::vector<mutation<int>*>& mut_str, 
const std::vector<reproductive_strategy<int>*>& rep_str, const std::vector<crossover<int,decltype(dist_func)>*>& cros_str,
const std::vector<end_condition<int>*>& end_cond, const Adaptation_func& adapt_func, const Comparator& compare_func, std::size_t genotype_size):selection_strategies(sel_str),mutation_strategies(mut_str),reproductive_strategies(rep_str),
crossover_strategies(cros_str), end_conditions(end_cond), adapt_func(adapt_func), compare_func(compare_func), genotype_size(genotype_size){}

void start_menu(){
    int decision=-1;
    while(decision!=4){
        std::cout <<"\tMENU\n";
        std::cout <<"1)Configure\n2)Set data\n3)Start algorithm\n4)Exit\n";
        while(decision<1 && decision>4){
            std::cout <<"\nDecision: ";
            std::cin >>decision;
        }
        switch(decision){
            case 1 : configure();
            case 2 : set_size();
            case 3 : start();
            case 4 : exit();
        }
    }
    
}

void set_data(){
    int decision=-1;
    std::size_t value=-1;
    while(decision!=3){
        std::cout <<"\tMENU\n";
        std::cout <<"1)Population size\n2)Mutation chance\n3)Exit\n";
        while(decision<1 && decision>3){
            std::cout <<"\nDecision: ";
            std::cin >>decision;
        }
        if(decision!=3){
            while(value<0){
                std::cout <<"\nValue: ";
                std::cin >>value;
            }
        }
        switch(decision){
            case 1 : population_size=value;
            case 2 : mutation_chance=value;
            case 3 : return;
        }
    }
}


void start(){
    if(forming_str==nullptr){
        std::cout <<"Choose forming algorithm!\n";
        return;
    }
    if(selection_str==nullptr){
        std::cout <<"Choose selection strategy!\n";
        return;
    }
    if(mutation_str==nullptr){
        std::cout <<"Choose mutation algorithm!\n";
        return;
    }
    if(reproductive_str==nullptr){
        std::cout <<"Choose reproduction strategy!\n";
        return;
    }
    if(crossover_str==nullptr){
        std::cout <<"Choose crossover algorithm!\n";
        return;
    }
    if(end_cond==nullptr){
        std::cout <<"Choose ending condition!\n";
        return;
    }
    auto pool=(*forming_str)(genotype_size,population_size,adapt_func);
    auto algorithm=algorithm_configuration<crossover<int,Adaptation_func>,mutation<int>,reproductive_strategy<int>,selection_strategy<int,Comparator>,end_condition<int>>(
        crossover_str,mutation_str,reproductive_str,selection_str,end_cond
    );
    algorithm(pool,adapt_func,compare_func,mutation_chance);
}

void configure(){
    int decision=-1;
    while(decision!=7){
        std::cout <<"\tConfiguration\n";
        std::cout <<"1)Start population forming method\n2)Selection strategy\n3)Mutation algorithm\n4)Reproduction strategy\n5)Crossover algorithm\n6)End condition\n7)Menu\n";
        while(decision<1 && decision>7){
            std::cout <<"\nDecision: ";
            std::cin >>decision;
        }
        switch(decision){
            case 1 : set_option(forming_strategies_names,forming_strategies,forming_str);
            case 2 : set_option(selection_strategies_names,selection_strategies,selection_str);
            case 3 : set_option(mutation_strategies_names,mutation_strategies,mutation_str);
            case 3 : set_option(reproductive_strategies_names,reproductive_strategies,reproductive_str);
            case 3 : set_option(crossover_strategies_names,crossover_strategies,crossover_str);
            case 3 : set_option(end_conditions_names,end_conditions,end_cond);
            case 7 : return;
        }
    }
}

template<typename Option>
void set_option(const std::vector<string>& option_names, std::vector<Option*> option_list, Option* target){
    int decision=-1;
    for(int i=0;i<option_names.size();i++){
        std::cout <<i+1<<") "<<option_names[i]<<"\n";
    }
    while(decision<1 && decision>option_names.size()){
        std::cout <<"\nDecision: ";
        std::cin >>decision;
    }
    target=option_list[decision-1];
}

std::vector<std::string> forming_strategies_names;
std::vector<std::string> selection_strategies_names;
std::vector<std::string> mutation_strategies_names;
std::vector<std::string> reproductive_strategies_names;
std::vector<std::string> crossover_strategies_names;
std::vector<std::string> end_conditions_names;

std::vector<forming_algorithm<Adaptation_func>*> forming_strategies;
std::vector<selection_strategy<int,Comparator>*> selection_strategies;
std::vector<mutation<int>*> mutation_strategies;
std::vector<reproductive_strategy<int>*> reproductive_strategies;
std::vector<crossover<int,decltype(Adaptation_func)>*> crossover_strategies;
std::vector<end_condition<int>*> end_conditions;

forming_algorithm<Adaptation_func>* forming_str=nullptr;
selection_strategy<int,Comparator>* selection_str=nullptr;
mutation<int>* mutation_str=nullptr;
reproductive_strategy<int>* reproductive_str=nullptr;
crossover<int,decltype(Adaptation_func)>* crossover_str=nullptr;
end_condition<int>* end_cond=nullptr;

std::size_t genotype_size;
std::size_t mutation_chance;
const Adaptation_func& adapt_func;
const Comparator& compare_func;
std::size_t population_size=0;
};
