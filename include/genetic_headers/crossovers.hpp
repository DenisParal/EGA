#include "includes.h"

class npoint_crossover{
public:
    npoint_crossover(std::vector<int>& positions):positions(positions){}
    template<typename T, typename Adapt_func>
    std::vector<std::shared_ptr<individual<T>>> operator()(const std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>& parents, const Adapt_func& func, std::size_t offspring_size=2){
    std::vector<std::shared_ptr<individual<T>>> offspring;
    std::size_t size=parents.first->size();
    std::vector<T> fgenotype(size);
    std::vector<T> sgenotype(size);
    std::size_t index=0;
    bool changed=false;
    for(std::size_t i=0;i<size;i++){
        if(i==positions[index]&&index<positions.size()){
            changed=!changed;
            ++index;
        }
        if(changed){
            fgenotype[i]=parents.second->at(i);
            sgenotype[i]=parents.first->at(i);
        }else{
            fgenotype[i]=parents.first->at(i);
            sgenotype[i]=parents.second->at(i);
        }
    }
    offspring.push_back(std::make_shared<individual<T>>(fgenotype,func));
    offspring.push_back(std::make_shared<individual<T>>(sgenotype,func));
    return offspring;
}
std::vector<int> positions;
};

class homogen_equal_crossover{
public:
    template<typename T, typename Adapt_func>
    std::vector<std::shared_ptr<individual<T>>> operator()(const std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>& parents, const Adapt_func& func, std::size_t offspring_size=2){
    std::vector<std::shared_ptr<individual<T>>> offspring;
    std::size_t size=parents.first->size();
    std::vector<std::vector<T>> genotypes(offspring_size,std::vector<T>(size));
    int chance;
    for(std::size_t i=0;i<offspring_size;i++){
        for(int j=0;j<size;j++){
            chance=rand()%2;
            if(chance==0){
                genotypes[i][j]=parents.first->at(j);
            }else{
                genotypes[i][j]=parents.second->at(j);
            }
        }
    }
    for(auto& x:genotypes){
        offspring.push_back(std::make_shared<individual<T>>(x,func));
    }
    return offspring;
}
};


class order_crossover{
public:
    template<typename T, typename Adapt_func>
    std::vector<std::shared_ptr<individual<T>>> operator()(const std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>& parents, const Adapt_func& func, std::size_t offspring_size=2){
    std::vector<std::shared_ptr<individual<T>>> offspring;
    std::size_t size=parents.first->size();
    std::vector<std::vector<T>> genotypes(offspring_size,std::vector<T>(size));
    int chance;
    for(std::size_t i=0;i<offspring_size;i++){
        for(int j=0;j<size;j++){
            chance=rand()%2;
            if(chance==0){
                genotypes[i][j]=parents.first->at(j);
            }else{
                genotypes[i][j]=parents.second->at(j);
            }
        }
    }
    for(auto& x:genotypes){
        offspring.push_back(std::make_shared<individual<T>>(x,func));
    }
    return offspring;
}
};