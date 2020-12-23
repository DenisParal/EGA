#include "includes.h"

template<typename Adapt_func>
class forming_algorithm{
public:
virtual std::vector<std::shared_ptr<individual<int>>> operator()(std::size_t individ_size, std::size_t pop_size,const Adapt_func& func)=0;
};

template<typename Adapt_func>
class random_forming_algorithm : public forming_algorithm<Adapt_func>{
public:
std::vector<std::shared_ptr<individual<int>>> operator()(std::size_t individ_size, std::size_t pop_size,const Adapt_func& func){
    std::vector<std::shared_ptr<individual<int>>> result;
    std::vector<int> base;
    std::vector<int> order(individ_size);
    int pos;
    for(std::size_t i=0;i<pop_size;i++){
        for(int j=0;j<individ_size;j++){
            base.push_back(j);
            order[j]=rand()%individ_size;
        }
        for(int j=0;j<individ_size;j++){
            pos=rand()%base.size();
            order[j]=base[pos];
            base.erase(base.begin()+pos);
        }
        result.push_back(std::make_shared<individual<int>>(order,func));
    }
    return result;
}
};
