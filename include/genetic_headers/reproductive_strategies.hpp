#include "includes.h"
#include <random>
#include <algorithm>

class random_reproductive_strategy{
public:
template<typename T>
std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> operator()(std::vector<std::shared_ptr<individual<T>>> population){
    std::size_t size=population.size();
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> result;
    std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>> candidate;
    std::size_t pos1,pos2;
    while(size>1){
        pos1=rand()%size;
        candidate.first=population[pos1];
        population.erase(population.begin()+pos1);
        --size;
        pos2=rand()%size;
        candidate.first=population[pos2];
        population.erase(population.begin()+pos2);
        result.push_back(candidate);
        --size;
    }
    return result;
}
};
 
class inbreeding_reproductive_strategy{
public:
inbreeding_reproductive_strategy(std::size_t distance):distance(distance){}
template<typename T>
std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> operator()(std::vector<std::shared_ptr<individual<T>>> population){
    std::size_t size=population.size();
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> result;
    std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>> candidate;
    std::size_t pos1,pos2;
    while(size>1){
        pos1=rand()%size;
        candidate.first=population[pos1];
        population.erase(population.begin()+pos1);
        --size;

        for(int i=0;i<size;i++){
            if(get_distance(*population[i],*(candidate.first))<=distance){
                candidate.second=population[i];
                population.erase(population.begin()+i);
                --size;
                result.push_back(candidate);
                break;
            }
        }
    }
    return result;
}
private:
std::size_t distance;
};

class outobreeding_reproductive_strategy{
public:
outobreeding_reproductive_strategy(std::size_t distance):distance(distance){}
template<typename T>
std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> operator()(std::vector<std::shared_ptr<individual<T>>> population){
    std::size_t size=population.size();
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> result;
    std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>> candidate;
    std::size_t pos1,pos2;
    while(size>1){
        pos1=rand()%size;
        candidate.first=population[pos1];
        population.erase(population.begin()+pos1);
        --size;
        for(int i=0;i<size;i++){
            if(get_distance(*population[i],*(candidate.first))>=distance){
                candidate.second=population[i];
                population.erase(population.begin()+i);
                --size;
                result.push_back(candidate);
                break;
            }
        }
    }
    return result;
}
std::size_t distance;
};


class positive_assotiative_reproductive_sterategy{
public:
template<typename T>
std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> operator()(std::vector<std::shared_ptr<individual<T>>> population){
    std::size_t size=population.size();
    long sum_adapt_value=0;
    for(auto x: population){
        sum_adapt_value+= x->adapt();
    }
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> result;
    std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>> candidate;
    std::size_t pos1,pos2;
    long double chance;
    while(population.size()>1){
        if(sum_adapt_value>0){
            chance=rand()%sum_adapt_value;
        }else{
            chance=rand();
        }
        for(int i=0;i<population.size();i++){
            if(chance<=population[i]->adapt()){
                candidate.first=population[i];
                population.erase(population.begin()+i);
                sum_adapt_value-=candidate.first->adapt();
                --size;
                break;
            }else{
                chance-=population[i]->adapt();
            }
        }
        if(sum_adapt_value>0){
            chance=rand()%sum_adapt_value;
        }else{
            chance=rand();
        }
        for(int i=0;i<population.size();i++){
            if(chance<=population[i]->adapt()){
                candidate.second=population[i];
                population.erase(population.begin()+i);
                sum_adapt_value-=candidate.second->adapt();
                --size;
                result.push_back(candidate);
                candidate.first=std::shared_ptr<individual<T>>();
                candidate.second=std::shared_ptr<individual<T>>();
                break;
            }else{
                chance-=population[i]->adapt();
            }
        }
    }
    return result;
}
};

class negative_assotiative_reproductive_sterategy{
public:
template<typename T>
std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> operator()(std::vector<std::shared_ptr<individual<T>>> population){
    std::size_t size=population.size();
    std::size_t sum_adapt_value=0;
    for(auto x: population){
        sum_adapt_value+= x->adapt();
    }
    std::vector<std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>>> result;
    std::pair<std::shared_ptr<individual<T>>,std::shared_ptr<individual<T>>> candidate;
    std::size_t pos1,pos2;
    long double chance;
    while(size>1){
        if(sum_adapt_value>0){
            chance=rand()%sum_adapt_value;
        }else{
            chance=rand();
        }
        for(int i=0;i<size;i++){
            if(chance<=population[i]->adapt()){
                candidate.first=population[i];
                population.erase(population.begin()+i);
                sum_adapt_value-=candidate.first->adapt();
                --size;
                break;
            }else{
                chance-=population[i]->adapt();
            }
        }
        if(sum_adapt_value>0){
            chance=rand()%sum_adapt_value;
        }else{
            chance=rand();
        }
        for(int i=0;i<size;i++){
            if(chance>=population[i]->adapt()){
                candidate.second=population[i];
                population.erase(population.begin()+i);
                sum_adapt_value-=candidate.second->adapt();
                --size;
                result.push_back(candidate);
                candidate.first=std::shared_ptr<individual<T>>();
                candidate.second=std::shared_ptr<individual<T>>();
                break;
            }else{
                chance+=population[i]->adapt();
            }
        }
    }
    return result;
}
};