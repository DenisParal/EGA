#include "includes.h"
#include "genetic_algorithm.hpp"
#include <fstream>

std::ifstream fin;

int main(){

    std::string filename;
    std::cout <<"Enter filename: ";
    std::cin >> filename;
    fin.open(filename);
    int size;
    fin >> size;
    std::vector<std::vector<float>> matr(size,std::vector<float>(size));
    for(int i=0;i<size;i++){
        for(int j=0; j<size; j++){
            fin >> matr[i][j];
        }
    }

    std::srand(std::time(nullptr));
    std::vector<std::shared_ptr<individual<int>>> pop;

    
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return pow((convert(genotype,2)-pow(2,genotype.size()-1)),2);
    };

    auto dist_func=[=](const std::vector<int>& genotype){
        int sum=0;
        for(int i=0;i<genotype.size()-1;i++){
            sum+=matr[genotype[i]][genotype[i+1]];
        }
        return sum;
    };

    auto dist_optimum=[](const std::vector<std::shared_ptr<individual<int>>>& pop){
        std::shared_ptr<individual<int>> best_individ=pop[0];
        for(auto x:pop){
            if(x->adapt()<best_individ->adapt()){
                best_individ=x;
            }
        }
        return best_individ;
    };

    for(long i=0;i<32;i++){
        pop.push_back(std::make_shared<individual<int>>(parse_func(i,2,6),adapt_func));
    }

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

            //selection_test

    // auto sel=stable_select_strategy(50);
    // auto mut=point_mut();
    // auto reprod=positive_assotiative_reproductive_sterategy();
    // auto cross=homogen_equal_crossover();
    // auto e_cond=max_generation_cond(10);

    // auto algorithm=algorithm_configuration<homogen_equal_crossover,point_mut,positive_assotiative_reproductive_sterategy,stable_select_strategy,max_generation_cond>(
    //     cross,mut,reprod,sel,e_cond
    // );
    // algorithm(pop,adapt_func,20);

    individual<int> first({0,2,4,1,3},dist_func);
    individual<int> second({3,4,0,2,1},dist_func);
    print_key(first);
    std::cout <<" "<<first.adapt()<<"\n";
    print_key(second);
    std::cout <<" "<<second.adapt()<<"\n";
    std::pair<std::shared_ptr<individual<int>>,std::shared_ptr<individual<int>>> pair(std::make_shared<individual<int>>(first),std::make_shared<individual<int>>(second));
    std::vector<int> positions{1,3};
    auto offspring = npoint_ordered_crossover(positions)(pair,dist_func);

    for(auto x:offspring){
        print_key(*x);
        std::cout <<" "<<x->adapt()<<"\n";
    }
    point_ordered_mut()(offspring[0]);
    print_key(*(offspring[0]));

    // std::vector<int> v{3,5,1,4,2};
    // auto rv=order_code(v);
    // print_key(rv);
    // std::cout <<"\n\n";
    // rv=order_decode(v,rv);
    // print_key(rv);
}