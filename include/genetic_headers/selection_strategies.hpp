#include "includes.h"

class stable_select_strategy{
public:
stable_select_strategy(int new_gen_percent):percentage(new_gen_percent){}
template<typename T>
std::vector<std::shared_ptr<individual<T>>> operator()(std::vector<std::shared_ptr<individual<T>>>& old_gen, std::vector<std::shared_ptr<individual<T>>>& new_gen){
    std::vector<std::shared_ptr<individual<T>>> result_gen;

    std::size_t new_gen_size=(new_gen.size()*percentage)/100;
    std::size_t old_gen_size=old_gen.size()-new_gen_size;

    std::size_t sum_old_adapt_value=0;
    long chance;
    for(auto x: old_gen){
        sum_old_adapt_value+= x->adapt();
    }

    std::size_t sum_new_adapt_value=0;
    for(auto x: new_gen){
        sum_new_adapt_value+= x->adapt();
    }

    bool selector=false;
    while(old_gen_size>0 || new_gen_size>0){
        if(selector && old_gen_size>0 ||new_gen_size==0){
            if(sum_old_adapt_value>0){
                chance=rand()%sum_old_adapt_value;
            }else{
                chance=rand();
            }
            for(int i=0;i<old_gen.size();i++){
                if(chance<=old_gen[i]->adapt()){
                    sum_old_adapt_value-=old_gen[i]->adapt();
                    result_gen.push_back(old_gen[i]);
                    old_gen.erase(old_gen.begin()+i);
                    --old_gen_size;
                    selector=false;
                    break;
                }
            }
        }else{
            if(sum_new_adapt_value>0){
                chance=rand()%sum_new_adapt_value;
            }else{
                chance=rand();
            }
            for(int i=0;i<new_gen.size();i++){
                if(chance<=new_gen[i]->adapt()){
                    sum_new_adapt_value-=new_gen[i]->adapt();
                    result_gen.push_back(new_gen[i]);
                    new_gen.erase(new_gen.begin()+i);
                    --new_gen_size;
                    selector=true;
                    break;
                }
            }
        }
    }
    return result_gen;
}
int percentage;
};