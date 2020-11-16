#include "includes.h"
#include "BFS_alg.h"

int main(){
    srand(time(0));
    const long src_size=32768;
    population<int> pop;
    auto adapt_func= [](const std::vector<int>& genotype){
        return (rand()%101);
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,15),adapt_func));
    }
    auto val =BFS_algo(pop,[](std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    }, 10);
}