#include "includes.h"
#include "DFS_alg.h"

int main(){
    srand(time(0));
    int number_of_passes;
    std::cout <<"Enter loop count: ";
    std::cin >> number_of_passes;
    const long src_size=32;
    population<int> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return convert(genotype, 2);
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,5),adapt_func));
    }
    for(int i=0;i<32;i++){
        print_key(*(pop.at(i)));
        std::cout <<" "<< pop.at(i)->adapt();
        std::cout <<"\n";
    }
    auto val =DFS_algo(pop,[](std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    }, 5);
}