#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "Genetic.h"


template<typename Iterator>
void reverse(Iterator& begin, Iterator& end) {
    while (end - begin > 2) {
        std::swap(*begin, *end);
        ++begin;
        --end;
    }
}

std::vector<int> parse_func(long int value, long int power, long key_length) {
    std::vector<int> result;
    while (value > 0) {
        if (result.size() == key_length) {
            throw(std::invalid_argument("There is not enough space in key_length"));
        }
        result.push_back(value % power);
        value /= power;
    }
    if (result.size() < key_length) {
        long int size = result.size();
        for (int i = 0; i < key_length - size; i++) {
            result.push_back(0);
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

template<typename Container>
long convert(const Container& num, int power) {
    long result=0;
    for(int i=0;i<num.size();i++){
        result+=std::pow(power,i)*num[i];
    }
    return result;
}

// +ToDO: solve the problem with missing Keys qualifier when it is const&

template<typename Key_type>
int get_distance(const Key_type& first_key, const Key_type& second_key) {
    if (first_key.size() != second_key.size()) {
        throw(std::invalid_argument("Keys have different lenght"));
    }
    int result = 0;
    for (int i = 0; i < first_key.size(); i++) {
        result += (first_key[i] + second_key[i]) % 2;
    }
    return result;
}

template<typename Key_type>
void print_key(const Key_type& key){
    std::cout <<"[";
    for(auto& x: key){
        std::cout <<x <<" ";
    }
    std::cout <<"]";
}
template<typename Key_type>
void print_pair(const std::pair<Key_type, long>& pair) {
    print_key(*(pair.first));
    std::cout << " (" << pair.second << ")";
}

template<typename Key_type>
void print_algo_result(const std::pair<Key_type,long>& result){
    std::cout << "*****Algorithm result: pair<";
    print_pair(result);
    std::cout << ">*****\n";
}

template<typename Container, typename Key_type>
Container get_neighbours(const Container& pool, Key_type& key) {
    Container result;
    for (int i = 0; i < pool.size(); i++) {
        if (get_distance(*key, *(pool[i])) == 1) {
            result.add(pool[i]);
        }
    }
    return result;
}

//-ToDO

template<typename Container, typename Predicate>
std::vector<typename Container::value_type> selection(const Container& set, const Predicate& selector){
    std::vector<typename Container::value_type> result;
    for (auto& elem: set){
        if(selector(*elem)){
            result.push_back(std::make_shared<typename Container::value_type>(elem));
        }
    }
    return result;
}

template<typename Container, typename Predicate, typename Executor>
void apply_for_selected(Container& set, const Predicate& selector, const Executor& executor){
    for (auto& elem: set){
        if(selector(*elem)){
            executor(*elem);
        }
    }
}

template<typename Key_type>
Key_type modulo_addition(const Key_type& key1, const Key_type& key2, int mod){
    if(key1.size()!=key2.size()){
    throw(std::out_of_range("Keys have different sizes"));
    }
    Key_type result=key1;
    for(int i=0;i<key1.size();i++){
        result[i]=(key1[i]+key2[i])%mod;
    }
    return result;
}

//TODO Doesn't work problem might be in operator% with values<0, investigate it
template<typename Key_type>
void shift_loop(Key_type& key, int shift_value){
    //shift_value%=key.size();
    typename Key_type::value_type tmp=key[0];
    typename Key_type::value_type tmp_swap=0;
    int npos;
    int j=0;
    for(int i=0;i<key.size();i++){
        npos=(j+shift_value)%key.size();
        tmp_swap=tmp;
        tmp=key[npos];
        key[npos]=tmp_swap;
        j=npos;
    }
}
//~TODO
template<typename Key_type>
Key_type simpl_shift(const Key_type& key, int shift_value){
    Key_type tmp=key;
    if(shift_value<0){
        for(int i=0;i<key.size();i++){
            if(i-shift_value>=key.size()){
                tmp[i]=0;
            }else{
                tmp[i]=key[i-shift_value];
            }
        }
    }else if(shift_value>0){
        for(int i=key.size()-1;i>=0;i--){
            if(i-shift_value<0){
                tmp[i]=0;
            }else{
                tmp[i]=key[i-shift_value];
            }
        }
    }
    return tmp;
}

template<typename Key_type>
Key_type to_Grey(const Key_type& key){
    Key_type shifted_k=simpl_shift(key,1);
    Key_type tmp=modulo_addition(key,shifted_k,2);
    return modulo_addition(key,simpl_shift(key,1),2);
}

template<typename Key_type>
Key_type out_Grey(const Key_type& key){
    Key_type shifted_k=key;
    for(int i=1;i<key.size();i++){
        shifted_k=modulo_addition(shifted_k,simpl_shift(key,i),2);
    }
    return shifted_k;
}