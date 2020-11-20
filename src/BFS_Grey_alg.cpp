#include "includes.h"
#include "BFS_with_Grey.h"

int main(){
    srand(time(0));
    const long src_size=32;
    population<int> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return (rand()%101);
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,5),adapt_func));
    }
    for(int i=0;i<32;i++){
        print_key(*(pop.at(i)));
        std::cout <<" "<< pop.at(i)->adapt();
        std::cout <<"\n";
    }
    auto val =BFS_Grey_algo(pop,[](std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    }, 10);
}