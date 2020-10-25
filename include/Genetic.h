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
    void print_genotype() const {
        std::cout << "[";
        for (auto x : genstring) {
            std::cout << x;
        }
        std::cout << "] ";
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
class population {
public:
    population() = default;
    template<typename functor>
    population(const population& another_population):individuals(another_population.individuals), population_size(another_population.population_size) {}
    population(population&& another_population) :individuals(std::move(another_population.individuals)), population_size(another_population.population_size) {}
    
    genotype<T>& operator[](int index) const {
        return individuals[i];
    }
    population& operator=(const population& another_population) {
        population_size = another_population.population_size;
        individuals = another_population.individuals;
        return *this;
    }
    population& operator=(population&& another_population) {
        if (&another_field != this) {
            population_size = another_population.population_size;
            individuals = std::move(another_population.individuals);
        }
        return *this;
    }

    void print_all() const {
        for (int i = 0; i < population_size; i++) {
            std::cout << "Elem (" << i << "): ";
            individuals[i].print_genotype();
            std::cout <<"\n";
        }
    }
    long int size() const {
        return population_size;
    }
    void add(genotype<T>& genstring) {
        individuals.push_back(genstring);
        ++population_size
    }
    void erase(int index) {
        individuals.erase(individuals.begin() + index);
        --population_size;
    }
    
private:
    std::vector<genotype<T>> individuals;
    long int population_size=0;
};