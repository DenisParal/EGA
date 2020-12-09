#include "includes.h"
#include "Monte_Carlo_alg.h"

int main(){
    srand(time(0));
    const long src_size=32768;
    population<int> pop;
    auto adapt_func= [](const std::vector<int>& genotype){
        return (rand()%1001);
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,15),adapt_func));
    }

    for(int i=0;i<32;i++){
        print_key(*(pop.at(i)));
        std::cout <<" "<< pop.at(i)->adapt();
        std::cout <<"\n";
    }
    for(int i=0;i<5;i++){
        auto val =MK_algo(pop,[](std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
        }, 5);
    }
}