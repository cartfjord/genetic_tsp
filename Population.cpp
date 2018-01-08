#include "Population.h"

void Population::sort(){
    std::sort(population.begin(), population.end());

}

Population::Population(unsigned int pop_size, vector< vector<double> > *dist_lookup){
    assert(pop_size <= MAX_POP_SIZE);
    
    this->dist_lookup = dist_lookup;
    num_cities = dist_lookup->size();

    population.reserve(pop_size);
    for(int i = 0; i < pop_size; i++){
        population.push_back(Chromosome(num_cities));
        population[i].compute_fitness(*dist_lookup);
    }

    current_pop_size = pop_size;

}

void Population::selection(int n_best){
    assert(n_best > 1 && n_best < MAX_POP_SIZE);
    sort();
    while(current_pop_size > n_best){
        population.pop_back();
        current_pop_size--;
    }
    
}

void Population::mutation(double mutation_rate_scramble, double mutation_rate_inversion){
    assert(mutation_rate_scramble >= 0 && mutation_rate_scramble < 1);
    assert(mutation_rate_inversion >= 0 && mutation_rate_inversion < 1);
    
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0.0, 1.0);
    
    for(int i = 0; i < current_pop_size; i++){
        
        if(dis(gen) < mutation_rate_inversion){
            population[i].inversion_mutation();
        }

        if(dis(gen) < mutation_rate_scramble){
            population[i].scramble_mutation();
        }
    }
}

void Population::crossover(int new_size){
    int possible_parents = current_pop_size;

    int i = 0;
    while(current_pop_size < new_size){
        int mother_idx = rand() % possible_parents;
        int father_idx = rand() % possible_parents;

        Chromosome Child;
        Child.crossover(&population[father_idx], &population[mother_idx]);
        Child.compute_fitness(*dist_lookup);
        population.push_back(Child);
        
        current_pop_size++;
    }
}

Chromosome Population::get_best_chromosome(){
    return population[0];
}

ostream &operator<<(ostream &os, const Population &rhs){
    for(int i = 0; i < rhs.current_pop_size; i++){
        os << "Chromosome: " << i << ", " << rhs.population[i] << endl << endl;
    }

    return os;
}
