#include "includes.h"

class max_generation_cond{
public:
max_generation_cond(long , int max_generation_number):max_generation_number(max_generation_number){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>&, const std::shared_ptr<individual<T>>&){
    ++generation_number;
    if(generation_number<=max_generation_number){
        return true;
    }
    return false;
}
int max_generation_number;
int generation_number=1;
};

class max_adaptation_cond{
public:
max_adaptation_cond(long start_value, int max_stagnation_duration):last_adapt_maximum(start_value),max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    if(best_individ->adaptation_value>last_adapt_maximum){
       last_adapt_maximum=best_individ->adaptation_value;
       return true;
    }else{
        ++stagnation_duration;
        if(stagnation_duration>max_stagnation_duration){
            return false;
        }
    }
    return true;
}
long last_adapt_maximum;
int max_stagnation_duration;
int stagnation_duration=0;
};

class average_adaptation_cond{
public:
average_adaptation_cond(long start_value, int max_stagnation_duration):last_average_adapt(start_value),max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    long average_adapt=0;
    for(auto& individ: population){
        average_adapt+= individ->adaptation_value;
    }
    std::cout <<"\nCOND_LOG: current average: "<<average_adapt<<" max average: "<<last_average_adapt<<"\n\n";
    if(average_adapt>last_average_adapt){
       last_average_adapt=average_adapt;
       return true;
    }else{
        ++stagnation_duration;
        if(stagnation_duration>max_stagnation_duration){
            return false;
        }
    }
    return true;
}
long last_average_adapt;
int max_stagnation_duration;
int stagnation_duration=0;
};