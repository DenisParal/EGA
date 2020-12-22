#include "includes.h"
#include "genetic_algorithm.hpp"
#include <fstream>

std::ifstream fin;

template<typename T>
class base{
virtual void operator()(int x)=0;
};

template<typename T>
class derived : public base<T>{
void operator()(int x){
    std::cout <<x;
}
};
int main(){

    std::string filename;
    std::cout <<"Enter filename: ";
    std::cin >> filename;
    fin.open(filename);
    int size;
    fin >> size;
    std::vector<std::vector<float>> matr(size,std::vector<float>(size));
    for(int i=0;i<size;i++){
        for(int j=0; j<size; j++){
            fin >> matr[i][j];
        }
    }

    std::srand(std::time(nullptr));
    std::vector<std::shared_ptr<individual<int>>> pop;
    base<int>* el =new derived<int>();

}