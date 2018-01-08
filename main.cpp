#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#include "Map.h"
#include "Chromosome.h"
#include "Population.h"

#define POP_SIZE 500
#define POP_MUTATION_RATE_SCRAMBLE 0.02
#define POP_MUTATION_RATE_INVERSION 0.02
#define NUM_GENERATIONS 5000

int main(){
    srand(time(NULL));

    Map Europe("map.png");

    vector<KeyPoint> cities_ordered = Europe.get_cities_coords();
    vector< vector<double> > distances = Europe.get_cities_dists();
 

    vector<KeyPoint> cities_new_order;    
    Population pop(POP_SIZE, &distances);
    
    Chromosome current_best_chromosome;

    cities_new_order.reserve(cities_ordered.size());
    //namedWindow("Traveling Salesman Solution", WINDOW_AUTOSIZE);
    //moveWindow("Traveling Salesman Solution", 100, 100);
    //waitKey(0);
    for(int generation = 1; generation < NUM_GENERATIONS; generation++){
        pop.selection(POP_SIZE/2);
        cout << pop.get_best_chromosome() << endl;
        pop.mutation(POP_MUTATION_RATE_SCRAMBLE, POP_MUTATION_RATE_INVERSION);
        pop.crossover(POP_SIZE);

        if(pop.get_best_chromosome().get_fitness() < current_best_chromosome.get_fitness() ){
            current_best_chromosome = pop.get_best_chromosome();
            cities_new_order.clear();
            for(int i = 0; i < cities_ordered.size(); i++){
                cities_new_order.push_back(cities_ordered[current_best_chromosome.get_genes()[i]]);
            }

            Europe.plot_map_route(cities_new_order, 0.75);
        }

    }

    //waitKey(0);
    
}