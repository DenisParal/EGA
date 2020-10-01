#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>

template<typename Iterator>
void reverse(Iterator& begin, Iterator& end) {
    while (end - begin > 2) {
        std::swap(*begin, *end);
        ++begin;
        --end;
    }
}

class Field {
public:
    template<typename Functor>
    Field(long int field_size, int key_length, int power, const Functor& function) :field_size(field_size), key_length(key_length), power(power) {
        for (long int i = 0; i < field_size; i++) {
            std::vector<int> key = parse_func(i);
            keys.push_back(key);
            values.push_back(function(key));
        }
    }
    std::pair<std::vector<int>, long int> operator[](long int index) {
        return std::pair<std::vector<int>, long int>(keys[index], values[index]);
    }
    long int get_field_size() {
        return field_size;
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
            for (int i = 0; i < key_length - size;i++) {
                result.push_back(0);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
    std::vector<std::vector<int>> keys;
    std::vector<int> values;
    long int field_size;
    int key_length;
    int power;
};

std::pair<std::vector<int>, long int> MK_algo(Field& field, int N) {
    std::pair<std::vector<int>, long int> max({}, 0);
    std::pair<std::vector<int>, long int> temp_pair;
    for (int i = 0; i < N; i++) {

        std::cout << "Current max data: [";
        for (auto x : max.first)std::cout << x;
        std::cout << "] (" << max.second << ")\n";

        int position = rand() % field.get_field_size();
        temp_pair = field[position];

        std::cout << "Iteration data: [";
        for (auto x : temp_pair.first)std::cout << x;
        std::cout << "] (" << temp_pair.second << ")";

        if (temp_pair.second > max.second) {
            max = temp_pair;
            std::cout << "\nOptimizes";
        }
        std::cout << "\n\n";
    }
    std::cout << "*****Algorithm result: pair<[";
    for (auto x : max.first)std::cout << x;
    std::cout << "] (" << max.second << ")>*****\n";
    return max;
}

int main()
{
    srand(time(0));
    Field f( 10000,15,2,[](auto& vec) {
        int x = rand()%10000;
        return x;
    }
    );
    auto result = MK_algo(f, 10);
    auto result2 = MK_algo(f, 50);
    auto result3 = MK_algo(f, 100);
}
