#include "includes.h"

class point_mut{
public:
template<typename T>
void operator()(std::shared_ptr<individual<T>>& individ){
    std::size_t pos=rand()%individ->size()
    *individ[pos]=1-*individ[pos];
}
};

class saltation_mut{
public:
template<typename T>
void operator()(std::shared_ptr<individual<T>>& individ){
    std::size_t pos1=rand()%individ->size()
    std::size_t pos2=rand()%individ->size()
    std::swap(*individ[pos1],*individ[pos2]);
}
};

class inversion_mut{
public:
template<typename T>
void operator()(std::shared_ptr<individual<T>>& individ){
    std::size_t pos1=rand()%individ->size()
    std::size_t pos2=rand()%individ->size()
    for(std::size_t i=pos1;i<=pos2;i++){
        *individ[i]=1-*individ[i];
    }
}
};