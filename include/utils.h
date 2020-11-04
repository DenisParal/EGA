#pragma once
#include <vector>
#include <memory>
#include "Genetic.h"

std::vector<int>& parse_func(long int value, long int power, long key_length) {
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

template<typename Iterator>
void reverse(Iterator& begin, Iterator& end) {
    while (end - begin > 2) {
        std::swap(*begin, *end);
        ++begin;
        --end;
    }
}

template<typename Key_type>
void print_key(const Key_type& key){
    std::cout <<"[";
    for(auto& x: key){
        std::cout <<x <<" "
    }
    std::cout <<"]";
}
template<typename Key_type>
void print_pair(const std::pair<Key_type, long>& pair) {
    print_key(pair.first);
    std::cout << " (" << pair.second << ")";
}

template<typename Key_type>
void print_algo_result(const std::pair<Key_type,long>& result){
    std::cout << "Out of neibhours\n";
    std::cout << "*****Algorithm result: pair<";
    print_pair(result);
    std::cout << ">*****\n";
}

template<typename Container, typename Key_type>
Container get_neighbours(const Container& pool, const Key_type& key) {
    Container result;
    for (int i = 0; i < popul.size(); i++) {
        if (get_distance(key, popul[i]) == 1) {
            result.add(popul[i]);
        }
    }
    return result;
}

template<typename Container, typename Predicate>
std::vector<typename Container::value_type> selection(const Container& set, Predicate&& selector){
    std::vector<std::shared_ptr<typename Container::value_type>> result;
    for (auto& elem: set){
        if(selector(elem)){
            result.push_back(std::shared_ptr<typename Container::value_type>(elem));
        }
    }
    return result;
}

template<typename Container, typename Predicate, typename Executor>
void apply_for_selected(const Container& set, Predicate&& selector, Executor&& executor){
    for (auto& elem: set){
        if(selector(elem)){
            executor(elem);
        }
    }
}