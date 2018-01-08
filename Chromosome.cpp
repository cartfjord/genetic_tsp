#include "Chromosome.h"

int myrandom(int i){
    return rand()%i;
}

void Chromosome::swap(int *city_1_idx, int *city_2_idx){
    int tmp = *city_1_idx;
    *city_1_idx = *city_2_idx;
    *city_2_idx = tmp;
}

Chromosome::Chromosome(){
    fitness = DBL_MAX; //double maximum value, lower fitness i better.
}

Chromosome::Chromosome(unsigned int num_cities){
    fitness = DBL_MAX; //double maximum value, lower_fitness is better.

    for(int i = 0; i < num_cities; i++){
        genes.push_back(i);
    }

    randomize();
}

void Chromosome::randomize(vector<int> *genes){
    random_shuffle(genes->begin(), genes->end(), myrandom);
}
void Chromosome::randomize(){
    randomize(&(this->genes));
}

void Chromosome::compute_fitness(vector< vector<double> > distance_table){
    double tot_dist = 0;
    int num_cities = genes.size();

    for(int i = 0; i < num_cities; i++){
        tot_dist += distance_table[genes[i]][genes[(i+1) % num_cities]];
    }

    fitness = tot_dist;

    vector<int> test_unique = genes;
    std::sort(test_unique.begin(), test_unique.end());
    for(int i = 0; i < test_unique.size(); i++){
        assert(test_unique[i] == i);
    }
    
    
}

void Chromosome::inversion_mutation(){
    int idx_begin = rand() % genes.size();
    int idx_end = rand() % (genes.size() - idx_begin) + idx_begin;

    //Sanity Check
    assert(idx_begin >= 0 && idx_begin < genes.size());
    assert(idx_end >= 0 && idx_end < genes.size());   
    assert(idx_end - idx_begin >= 0);

    vector<int> genes_subset(&genes[idx_begin],&genes[idx_end]);

    reverse(genes_subset.begin(), genes_subset.end());
    
    copy(genes_subset.begin(), genes_subset.end(), genes.begin() + idx_begin);
    
}

void Chromosome::scramble_mutation(){
    int idx_begin = rand() % genes.size();
    int idx_end = rand() % (genes.size() - idx_begin) + idx_begin;

    vector<int> genes_subset(&genes[idx_begin],&genes[idx_end]);

    randomize(&genes_subset);

    copy(genes_subset.begin(), genes_subset.end(), genes.begin() + idx_begin);
}

void Chromosome::crossover(const Chromosome *father, const Chromosome *mother){
    int idx_crossover = rand() % father->genes.size();
    copy_n(father->genes.begin(), idx_crossover, back_inserter(this->genes));
    
    for(int i = 0; i < mother->genes.size(); i++){
        if(find(genes.begin(), genes.end(), mother->genes[i]) == genes.end()){
            this->genes.push_back(mother->genes[i]);
        }
    }
}

Chromosome &Chromosome::operator=(const Chromosome rhs){
    this->genes = rhs.genes;
    this->fitness = rhs.fitness;

    return *this;
}

ostream & operator<<(ostream &os, const Chromosome &rhs){
    os << "Fitness: " << rhs.fitness << endl;

    for(int i = 0; i < rhs.genes.size(); i++){
        os << rhs.genes[i] << " ";
    }

    return os;
}

bool operator<(Chromosome const &a, Chromosome const &b){
    return a.get_fitness() < b.get_fitness();
}

bool operator>(Chromosome const &a, Chromosome const &b){
    return a.get_fitness() > b.get_fitness();
}

vector<int> Chromosome::get_genes(){
    return genes;
}

double Chromosome::get_fitness() const{
    return fitness;
}