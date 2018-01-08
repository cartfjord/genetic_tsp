#pragma once
#include <opencv2/core/core.hpp>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <assert.h>
#include <numeric>

using namespace cv;
using namespace std;

class Chromosome{
    private:
    vector<int> genes;
    double fitness;

    void swap(int *city_1_idx, int *city_2_idx);

    public:
    Chromosome();
    Chromosome(unsigned int num_cities);

    void print();
    void randomize();
    void randomize(vector<int> *genes);
    void compute_fitness(vector< vector<double> > distance_table);
    void inversion_mutation();
    void scramble_mutation();
    void crossover(const Chromosome *father, const Chromosome *mother);

    Chromosome &operator=(const Chromosome rhs);
    friend ostream &operator<<(ostream &os, const Chromosome &rhs);

    friend bool operator<(Chromosome const &a, Chromosome const &b);
    friend bool operator>(Chromosome const &a, Chromosome const &b);

    vector<int> get_genes();
    double get_fitness() const;
};