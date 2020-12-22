#include "genetic_algorithm.hpp"
#include <fstream>

std::ifstream fin;

template<typename Adapt_func>
std::vector<std::shared_ptr<individual<int>>> generate_population(std::size_t individ_size, std::size_t pop_size,const Adapt_func& func){
    std::vector<std::shared_ptr<individual<int>>> result;
    std::vector<int> base;
    std::vector<int> order(individ_size);
    int pos;
    for(std::size_t i=0;i<pop_size;i++){
        for(int j=0;j<individ_size;j++){
            base.push_back(j);
            order[j]=rand()%individ_size;
        }
        for(int j=0;j<individ_size;j++){
            pos=rand()%base.size();
            order[j]=base[pos];
            base.erase(base.begin()+pos);
        }
        result.push_back(std::make_shared<individual<int>>(order,func));
    }
    return result;
}

int main(){
    std::srand(std::time(nullptr));

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

    auto decider=[](long double value_to_compare, long double value_to_compare_with){
        return value_to_compare>value_to_compare_with;
    };

    auto pool=generate_population(size,30,dist_func);
    long double sum_adapt=0;
    for(auto x:pool){
        print_key(*x);
        std::cout <<" "<<x->adapt()<<"\n";
        sum_adapt+=x->adapt();
    }

    std::vector<int> positions{1,3};

    auto sel=beta_tournament(5);
    auto mut=point_ordered_mut();
    auto reprod=positive_assotiative_reproductive_sterategy();
    auto cross=npoint_ordered_crossover(positions);
    auto e_cond=max_generation_cond(50);

    auto algorithm=algorithm_configuration<npoint_ordered_crossover,point_ordered_mut,positive_assotiative_reproductive_sterategy,beta_tournament,max_generation_cond>(
        cross,mut,reprod,sel,e_cond
    );
    algorithm(pool,dist_func,dist_optimum,decider,100);
}