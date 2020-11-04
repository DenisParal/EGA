#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

template<typename T>
class genotype {
public:
    genotype(const genotype& another_genotype):allelic_form(another_genotype.allelic_form), genstring(another_genotype.gentype) {}
    genotype(genotype&& another_genotype) :allelic_form(std::move(another_genotype.allelic_form)), genstring(std::move(another_genotype.genstring)) {}
    genotype& operator=(const genotype& another_genotype) {
        allelic_form = another_genotype.allelic_form;
        genstring = another_genotype.genstring;
        return *this;
    }
    genotype& operator=(genotype&& another_genotype) {
        if (this != &another_genotype) {
            allelic_form = std::move(another_genotype.allelic_form);
            genstring = std::move(another_genotype.genstring);
            return *this;
        }
    }
    template<typename pheno_func>
    auto get_phenotype(pheno_func&& func)->decltype(func(genstring)) const {
        return func(genstring);
    }
    auto begin(){
        return genstring.begin();
    }
    auto end(){
        return genstring.end();
    }
    long int size() const {
        return genstring.size();
    }
    T& operator[](int index) {
        return genstring[index];
    }
private:
    std::shared_ptr<std::vector<T>> allelic_form;
    std::vector<T> genstring;
};

template<typename T>
class Container {
public:
    Container() = default;
    template<typename functor>
    Container(const Container& another_population):individuals(another_population.individuals), population_size(another_population.population_size) {}
    Container(Container&& another_population) :individuals(std::move(another_population.individuals)), population_size(another_population.population_size) {}
    
    std::shared_ptr<genotype<T>>& operator[](int index) const {
        return individuals[i];
    }
    Container& operator=(const Container& another_population) {
        population_size = another_population.population_size;
        individuals = another_population.individuals;
        return *this;
    }
    Container& operator=(Container&& another_population) {
        if (&another_field != this) {
            population_size = another_population.population_size;
            individuals = std::move(another_population.individuals);
        }
        return *this;
    }

    void print_all() const {
        for (int i = 0; i < population_size; i++) {
            std::cout << "Elem (" << i << "): ";
            print_key(*individuals[i]);
            std::cout <<"\n";
        }
    }
    long int size() const {
        return population_size;
    }
    void add(const genotype<T>& genstring) {
        individuals.push_back(std::make_shared<genotype<T>>(genstring));
        ++population_size
    }
    void add(genotype<T>&& genstring){
        individuals.push_back(std::make_shared<genotype<T>>(std::move(genstring)));
        ++population_size;
    }
    void erase(int index) {
        individuals.erase(individuals.begin() + index);
        --population_size;
    }
    
    static typename value_type=T;

private:
    std::vector<std::shared_ptr<genotype<T>>> individuals;
    long int population_size=0;
};