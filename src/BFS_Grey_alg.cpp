#include "includes.h"
#include "BFS_with_Grey.h"

int main(){
    srand(time(0));
    int number_of_passes;
    std::cout <<"Enter loop count: ";
    std::cin >> number_of_passes;
    const long src_size=32;
    population<int> pop;
    
    auto adapt_func= [](const std::vector<int>& genotype){
        return pow((convert(genotype,2)-pow(2,genotype.size()-1)),2);
    };
    for(long i=0;i<src_size;i++){
        pop.add(individual<int>(parse_func(i,2,5),adapt_func));
    }
    for(int i=0;i<32;i++){
        print_key(*(pop.at(i)));
        std::cout <<" "<< pop.at(i)->adapt();
        std::cout <<"\n";
    }
    auto val =BFS_Grey_algo(pop,[](const std::shared_ptr<individual<int>>& key){
        return (*key).adapt();
    }, number_of_passes);
}