#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator ){
    this->seed = seed;
    this->iterations = iterations;
    this->population_size = population_size;
    this->solution_generator = solution_generator;
}

vector< Solution > GeneticAlgorithm::create_population(){
    vector< Solution > population;

    for( int i = 0; i < this->population_size; i++ ){
        Solution sol = this->solution_generator->random_greedy_generation(  Instance::instance()->get_path_vertices() );
        population.push_back( sol );
    }

    return population;
}
int GeneticAlgorithm::find_best( vector< Solution > population ){
    int position_best = 0;
    double fitness_best = population[ 0 ].get_objetive_function();
    double actual_fitness = 0.0;

    for( unsigned int i = 0; i < population.size(); i++ ){
        actual_fitness = population[ i ].get_objetive_function();
        if( fitness_best < actual_fitness ){
            fitness_best = actual_fitness;
            position_best = i;
        }
    }

    return position_best;
}

Solution GeneticAlgorithm::execute(){
    Solution best;
    vector< Solution > population;
    
    srand( this->seed );

    for( int i = 0; i < this->iterations; i++ ){
        if( i%100 == 0 ) cout << i << endl;
        population = this->create_population();

        int position_new_best = this->find_best( population );
        Solution new_best = population[ position_new_best ];

        if( best.get_objetive_function() < new_best.get_objetive_function() ){
            best = new_best;
        }
    }

    return best;
}