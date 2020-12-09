#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "utils.h"

struct item{
    item(int index, int weight, int value):index(index),weight(weight),value(value){}

    void print(){
        std::cout <<"Item nomber "<<index<<"; weight: "<<weight<<"; value: "<<value<<"\n";
    }

    int index;
    float weight;
    float value;
};
std::ifstream fin;

int main(){
    std::string filename;
    std::cout <<"Enter filename: ";
    std::cin >> filename;
    fin.open(filename);

    float max_w;
    float sum_v=0;
    float sum_w=0;
    int size;
    fin >> size;
    std::vector<item> store;
    std::vector<int> pack(size,0);
    float weight;
    float value;
    int index;
    for(int i=0;i<size;i++){
        fin >>index >>weight >>value;
        store.push_back(item(index,weight,value));
    }
    std::cout <<"Store:\n";
    for(auto x:store){
        x.print();
    }
    std::cout <<"\n";
    std::cout <<"Do you want to set max weight? (y/n): ";
    char ans;
    bool decision;
    while(true){
    std::cin >>ans;
        if(ans=='y'){
            decision=true;
            break;
        }else if(ans=='n'){
            decision=false;
            break;
        }else{
            std::cout <<"\n(y/n)?";
        }
    }
    if(!decision){
        sum_w=0;
        for(auto x: store){
        sum_w+=x.weight;
        }
        max_w=sum_w*0.6f;
        std::cout <<"Weight has been set to "<<max_w<<"\n";
    }else{
        std::cout <<"\nEnter max weight: ";
        std::cin >>max_w;
    }

    int best_pos;
    float cur_w=0;
    sum_w=0;
    for(int i=0;i<size;i++){
        std::cout <<"***STEP "<<i+1<<"***\n";
        std::cout <<"pack: ";
        for(auto x: pack){
            std::cout <<x;
        }
        std::cout <<"\n";
        std::cout <<"Current weight: "<<sum_w<<"/"<<max_w<<"\n";
        std::cout <<"Current value: "<<sum_v<<"\n";
        best_pos=optimum(store,[](const auto& candidat, const auto& max){
            return candidat.value>max.value;
        });
        std::cout <<"Best candidate: ";
        store[best_pos].print();
        if(sum_w+store[best_pos].weight<=max_w){
            std::cout <<"Item fits in a pack\n";
            sum_w+=store[best_pos].weight;
            sum_v+=store[best_pos].value;
            store[best_pos].value=-1;
            pack[best_pos]=1;
        }else {
            std::cout <<"Weight limit achieved\n\n";
            break;
        }
    }
    std::cout <<"***RESULTS***\n";
    std::cout <<"pack: ";
    for(auto x: pack){
        std::cout <<x;
    }
    std::cout <<"\n";
    std::cout <<"Current weight: "<<sum_w<<"/"<<max_w<<"\n";
    std::cout <<"Current value: "<<sum_v<<"\n";
}