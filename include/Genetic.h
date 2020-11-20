#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

template<typename T>
class population;

template<typename T>
class individual {
public:
    template<typename Adapt_func>
    individual(const std::vector<T>& genotype, const Adapt_func& func):genotype(genotype), adaptation_value(func(genotype)){}
    individual(std::vector<T>&& genotype):genotype(std::move(genotype)){
        adaptation_value=func(this.genotype);
    }

    individual(const individual& another_individual):genotype(another_individual.genotype), adaptation_value(another_individual.adaptation_value){}
    individual(individual&& another_individual):genotype(std::move(another_individual.genotype)), adaptation_value(another_individual.adaptation_value){}
    
    individual& operator=(const individual& another_individual) {
        adaptation_value=another_individual.adaptation_value;
        genotype = another_individual.genotype;
        return *this;
    }

    individual& operator=(individual&& another_individual) {
        if (this != &another_individual) {
            adaptation_value=another_individual.adaptation_value;
            genotype = std::move(another_individual.genotype);
        }
        return *this;
    }
    double adapt() const {
        return adaptation_value;
    }
    template<typename Adapt_func>
    void set_adaptation(const Adapt_func& func){
        adaptation_value=func(genotype);
    }
    auto begin() const {
        return genotype.begin();
    }
    auto end() const {
        return genotype.end();
    }
    long int size() const {
        return genotype.size();
    }
    T& operator[](int index) {
        return genotype[index];
    }
    const T at(int index) const {
        return genotype[index];
    }
    using value_type=T;
private:
    std::vector<T> genotype;
    double adaptation_value;
};

template<typename T>
class population {
public:
    population() = default;
    population(const population& another_population):individuals(another_population.individuals), population_size(another_population.population_size) {}
    population(population&& another_population) :individuals(std::move(another_population.individuals)), population_size(another_population.population_size) {}
    template<typename Adapt_func>
    population(const std::vector<std::vector<T>>& genotype_list, const Adapt_func& func){
        for(auto x: genotype_list){
            add(individual(x,func));
        }
    }
    std::shared_ptr<individual<T>>& operator[](int index) {
        return individuals[index];
    }
    const std::shared_ptr<individual<T>>& at(int index) const {
        return individuals[index];
    }
    population& operator=(const population& another_population) {
        population_size = another_population.population_size;
        individuals = another_population.individuals;
        return *this;
    }
    population& operator=(population&& another_population) {
        if (&another_population != this) {
            population_size = another_population.population_size;
            individuals = std::move(another_population.individuals);
        }
        return *this;
    }

    template<typename Adapt_func>
    void set_adaptation(const Adapt_func& func){
        for(auto x: individuals){
            (*x).set_adaptation(func);
        }
    }

    void print_all() const {
        for (int i = 0; i < population_size; i++) {
            std::cout << "Elem (" << i << "): ";
            print_key(*individuals[i]);
            std::cout <<" ("<<(*individuals[i]).adapt()<<")\n";
        }
    }
    long int size() const {
        return population_size;
    }
    void add(const individual<T>& genotype) {
        individuals.push_back(std::make_shared<individual<T>>(genotype));
        ++population_size;
    }
    void add(individual<T>&& genotype){
        individuals.push_back(std::make_shared<individual<T>>(std::move(genotype)));
        ++population_size;
    }
    void add(const std::shared_ptr<individual<T>>& genotype){
        individuals.push_back(genotype);
        ++population_size;
    }
    void add(std::shared_ptr<individual<T>>&& genotype){
        individuals.push_back(std::move(genotype));
        ++population_size;
    }
    void erase(int index) {
        individuals.erase(individuals.begin() + index);
        --population_size;
    }

    using value_type=std::shared_ptr<individual<T>>;
    
private:
    std::vector<std::shared_ptr<individual<T>>> individuals;
    long int population_size=0;
};