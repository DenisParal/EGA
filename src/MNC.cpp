#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

std::ifstream fin;

template<typename T>
void print_m(const std::vector<std::vector<T>>& matr){
    for(auto& x: matr){
        for (auto& y: x){
            std::cout <<y <<" ";
        }
        std::cout <<"\n";
    }
}
template<typename T>
int find_min(const std::vector<T>& range, int post){
    T min;
    int pos;
    for(int i=0;i<range.size();i++){
        if(range[i]==-1||i==post){
            continue;
        }
        min=range[i];
        pos=i;
        break;
    }

    for(int i=pos+1;i<range.size();i++){
        if(range[i]==-1||i==post){
            continue;
        }
        if(range[i]<min){
            min=range[i];
            pos=i;
        }
    }
    return pos;
}

template<typename T>
void erase_position(std::vector<std::vector<T>>& matr, int pos){
    for(int i=0;i<matr.size();i++){
        matr[i][pos]=-1;
    }
}

int main(){
    srand(time(0));
    std::string filename;
    std::cout <<"Enter filename: ";
    std::cin >> filename;
    fin.open(filename);
    int size;
    fin >> size;
    std::vector<std::vector<int>> matr(size,std::vector<int>(size));
    for(int i=0;i<size;i++){
        for(int j=0; j<size; j++){
            fin >> matr[i][j];
        }
    }
    int start=rand()%size;
    std::cout <<"Algorithm started with " <<start <<"'st point\n";
    std::vector<int> path;
    path.push_back(start);
    std::vector<int> first_p_dist=matr[start];
    long sum_distance=0;
    std::vector<int> candidats;

    for(int i=1;i<size;i++){
        std::cout <<"***STEP "<<i+1<<" ***\n";
        std::cout <<"Current path: ";
        for(auto& x:path){
            std::cout <<x <<" ";
            candidats.push_back(find_min(matr[x],x));
        }
        std::cout <<"\n";
        std::cout <<"Candidats:\n";
        int best_pos=0;
        int min=matr[path[0]][candidats[0]];
        for(int j=0;j<path.size();j++){
            std::cout << path[j]<<" --> "<<candidats[j] <<" Dist("<<matr[path[j]][candidats[j]] <<")\n";
            if(matr[path[j]][candidats[j]]<min){
                min=matr[path[j]][candidats[j]];
                best_pos=j;
            }
        }
        std::cout <<"Distance to nearest point ("<<candidats[best_pos]<<") is "<<min<<"\n";
        sum_distance+=min;
        std::cout <<"Summary distance is: "<<sum_distance<<"\n\n";
        erase_position(matr,path[best_pos]);
        erase_position(matr,candidats[best_pos]);
        path.insert(path.begin()+best_pos+1,candidats[best_pos]);
        candidats.clear();
    }
    std::cout <<"Final path: ";
    for(auto& x:path){
        std::cout <<x <<" ";
    }
    std::cout <<"\n";
    std::cout <<"Final distance: "<<sum_distance<<"\n";
    std::cout <<"Final loop distance: "<< sum_distance+first_p_dist[path[size-1]];
}