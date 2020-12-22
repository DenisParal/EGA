#include "includes.h"

class max_generation_cond{
public:
max_generation_cond(int max_generation_number):max_generation_number(max_generation_number){}
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
max_adaptation_cond(int max_stagnation_duration, long start_value):last_adapt_maximum(start_value),max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    if(best_individ->adapt()>last_adapt_maximum){
       last_adapt_maximum=best_individ->adapt();
       stagnation_duration=0;
       return true;
    }else{
        ++stagnation_duration;
        last_adapt_maximum=best_individ->adapt();
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

class min_adaptation_cond{
public:
min_adaptation_cond(int max_stagnation_duration):max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    if(last_adapt_minimum==-1){
        last_adapt_minimum=best_individ->adapt();
        return true;
    }else
    if(best_individ->adapt()<last_adapt_minimum){
       last_adapt_minimum=best_individ->adapt();
       stagnation_duration=0;
       return true;
    }else{
        ++stagnation_duration;
        last_adapt_minimum=best_individ->adapt();
        if(stagnation_duration>max_stagnation_duration){
            return false;
        }
    }
    return true;
}
long last_adapt_minimum=-1;
int max_stagnation_duration;
int stagnation_duration=0;
};

class average_adaptation_cond{
public:
average_adaptation_cond(int max_stagnation_duration, long start_value):last_average_adapt(start_value),max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    long average_adapt=0;
    for(auto& individ: population){
        average_adapt+= individ->adapt();
    }
    std::cout <<"\nCOND_LOG: current average: "<<average_adapt<<" last average: "<<last_average_adapt<<"\n\n";
    if(average_adapt>last_average_adapt){
       last_average_adapt=average_adapt;
       stagnation_duration=0;
       return true;
    }else{
        ++stagnation_duration;
        last_average_adapt=average_adapt;
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

class average_adaptation_cond_reversed{
public:
average_adaptation_cond_reversed(int max_stagnation_duration, long start_value):last_average_adapt(start_value),max_stagnation_duration(max_stagnation_duration){}
template<typename T>
bool operator()(const std::vector<std::shared_ptr<individual<T>>>& population, const std::shared_ptr<individual<T>>& best_individ){
    long average_adapt=0;
    for(auto& individ: population){
        average_adapt+= individ->adapt();
    }
    std::cout <<"\nCOND_LOG: current average: "<<average_adapt<<" last average: "<<last_average_adapt<<"\n\n";
    if(average_adapt<last_average_adapt){
       last_average_adapt=average_adapt;
       stagnation_duration=0;
       return true;
    }else{
        ++stagnation_duration;
        last_average_adapt=average_adapt;
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