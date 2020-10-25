#pragma once
#include <vector>
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

template<typename Container>
int get_distance(const Container& first_key, const Container& second_key) {
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

template<typename T>
void print_pair(const std::pair<genotype<T>, long>& pair) {
    pair.first.print_genotype();
    std::cout << " (" << pair.second << ")";
}

template<typename T>
void print_algo_result(const std::pair<genotype<T>,long>& result){
    std::cout << "Out of neibhours\n";
    std::cout << "*****Algorithm result: pair<";
    print_pair(result);
    std::cout << ">*****\n";
}