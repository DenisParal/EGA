#include "includes.h"

int main(){
    int shift_value;
    std::vector<int> v;
    std::vector<int> v2;
    std::vector<int> result;
    while(shift_value!=-1){
        std::cout <<"Bin: ";
        std::cin >>shift_value;
        result=to_Grey(parse_func(shift_value,2,3));
        print_key(result);
        std::cout <<"\n";
        result=out_Grey(result);
        print_key(result);
        std::cout <<"\n";
    }
}