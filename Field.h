#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>

class field {
public:
    field(int key_length, int power=2) : key_length(key_length), power(power) {}
    template<typename functor>
    field(long int field_size, int key_length, int power, const functor& function) : field_size(field_size), key_length(key_length), power(power) {
        for (long int i = 0; i < field_size; i++) {
            std::vector<int> key = parse_func(i);
            keys.push_back(key);
            values.push_back(function(key));
        }
    }
    field(const field& another_field):key_length(another_field.key_length),power(another_field.power) {
        for (int i = 0; i < another_field.field_size; i++) {
            keys.push_back(another_field.keys[i]);
            values.push_back(another_field.values[i]);
        }
    }
    field(field&& another_field) :keys(std::move(another_field.keys)), values(std::move(another_field.values)), field_size(another_field.field_size), key_length(another_field.key_length), power(another_field.power) {}
    
    
    field operator=(const field& another_field) {
        key_length = another_field.key_length;
        power = another_field.power;
        for (int i = 0; i < another_field.field_size; i++) {
            keys.push_back(another_field.keys[i]);
            values.push_back(another_field.values[i]);
        }
        return *this;
    }
    field operator=(field&& another_field) {
        if (&another_field != this) {
            key_length = another_field.key_length;
            power = another_field.power;
            keys = std::move(another_field.keys);
            values = std::move(another_field.values);
        }
        return *this;
    }
    std::pair<std::vector<int>, long int> operator[](long int index) {
        return std::pair<std::vector<int>, long int>(keys[index], values[index]);
    }


    template<typename functor>
    void add_with_rule(std::vector<int>& key, const functor& function) {
        keys.push_back(key);
        values.push_back(function(key));
        ++field_size;
    }
    void add_without_rule(const std::vector<int>& key, long int value) {
        keys.push_back(key);
        values.push_back(value);
        ++field_size;
    }
    void print_field() {
        for (int i = 0; i < field_size; i++) {
            std::cout << "Element (" << i << "): [";
            for (auto x : keys[i])std::cout << x;
            std::cout << "] (" << values[i] << ")\n";
        }
    }
    long int get_field_size() {
        return field_size;
    }
    int get_distance(const std::vector<int>& first_key, const std::vector<int>& second_key) {
        if (first_key.size() != second_key.size()) {
            throw(std::invalid_argument("Keys have different lenght"));
        }
        int result = 0;
        for (int i = 0; i < first_key.size(); i++) {
            result += (first_key[i] + second_key[i]) % 2;
        }
        return result;
    }
    void erase(int index) {
        keys.erase(keys.begin() + index);
        values.erase(values.begin() + index);
        --field_size;
    }
    field get_neighbours(const std::vector<int>& key) {
        field result(key.size());
        for (int i = 0; i < field_size; i++) {
            if (get_distance(key, keys[i]) == 1) {
                result.add_without_rule(keys[i], values[i]);
            }
        }
        return result;
    }
private:
    std::vector<int> parse_func(long int value) {
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
    std::vector<std::vector<int>> keys;
    std::vector<int> values;
    long int field_size=0;
    int key_length;
    int power;
};