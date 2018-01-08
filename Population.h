
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <random>
using namespace std;

#include "Chromosome.h"

#define MAX_POP_SIZE 100000

class Population{
    private:
        vector<Chromosome> population;
        int current_pop_size;
        
        vector< vector<double> > *dist_lookup;
        int num_cities;

        void sort(); //Sort chromosomes by fitness;

    public:
        Population(unsigned int pop_size, vector< vector<double> > *dist_lookup);
        void selection(int n_best);
        void mutation(double mutation_rate_scramble, double mutation_rate_inversion);
        void crossover(int new_size);

        Chromosome get_best_chromosome();

        friend ostream &operator<<(ostream &os, const Population &rhs);
};
