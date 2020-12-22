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


class dist_calculator{
public:
dist_calculator(const std::vector<std::vector<float>>& data):data(data){}
auto operator()(const std::vector<int>& path){
    long double sum=0;
    for(int i=0;i<path.size()-1;i++){
            sum+=data[path[i]][path[i+1]];
    }
    return sum;
}

std::vector<std::vector<float>> data;
};

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
    // for(auto x:pool){
    //     print_key(*x);
    //     std::cout <<" "<<x->adapt()<<"\n";
    //     sum_adapt+=x->adapt();
    // }

    std::vector<int> positions{1,3};

    selection_strategy<int,decltype(decider)>* sel= new beta_tournament<int,decltype(decider)>(5);
    mutation<int>* mut= new point_ordered_mut<int>();
    reproductive_strategy<int>* reprod= new positive_assotiative_reproductive_sterategy<int>();
    crossover<int,decltype(dist_func)>* cross = new npoint_ordered_crossover<int,decltype(dist_func)>(positions);
    end_condition<int>* e_cond = new max_generation_cond<int>(20);

    // auto res=(*cross)(std::pair<std::shared_ptr<individual<int>>,std::shared_ptr<individual<int>>>(pool[0],pool[1]),dist_func);

    // print_key(*(pool[0]));
    // std::cout <<"\n";
    // print_key(*(pool[1]));
    // std::cout <<"\n";
    // print_key(*(res[0]));
    // std::cout <<"\n";
    // print_key(*(res[1]));
    // std::cout <<"\n";

    auto algorithm=algorithm_configuration<crossover<int,decltype(dist_func)>,mutation<int>,reproductive_strategy<int>,selection_strategy<int,decltype(decider)>,end_condition<int>>(
        cross,mut,reprod,sel,e_cond
    );
    algorithm(pool,dist_func,dist_optimum,decider,30);
}