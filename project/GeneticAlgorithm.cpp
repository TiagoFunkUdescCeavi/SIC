#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator, Selection * selection, CrossOver * crossover, Mutation * mutation, LocalSearch * local_search, Replacement * replacement ){
    this->seed = seed;
    this->iterations = iterations;
    this->population_size = population_size;
    this->solution_generator = solution_generator;
    this->selection = selection;
    this->crossover = crossover;
    this->mutation = mutation;
    this->local_search = local_search;
    this->replacement = replacement;
}

vector< Solution > GeneticAlgorithm::create_population(){
    vector< Solution > population;

    for( int i = 0; i < this->population_size; i++ ){
        Solution sol = this->solution_generator->random_greedy_generation(  Instance::instance()->get_path_vertices() );
        population.push_back( sol );
    }

    return population;
}

vector< Solution > GeneticAlgorithm::apply_local_search( vector< Solution > population ){
    Solution sol;
    vector< Solution > new_population;

    for( unsigned int i = 0; i < population.size(); i++ ){
        sol = population[ i ];
        sol = this->local_search->execute( sol, this->check_unused_vertices( sol ) );
        new_population.push_back( sol );
    }

    return new_population;
}

vector< Vertice * > GeneticAlgorithm::check_unused_vertices( Solution sol ){
    int erase_position = 0;
    Vertice * v = 0;
    vector< Vertice * > vertices = Instance::instance()->get_path_vertices();
        
    for( int i = 0; i < sol.get_number_paths(); i++ ){
        for( int j = 1; j < sol.get_length_of_path( i ) - 1; j++ ){
            v = sol.get_vertice_in_path( i, j );

            for( unsigned int k = 0; k < vertices.size(); k++ ){
                if( v->get_hash() == vertices[ k ]->get_hash() ){
                    erase_position = k;
                    break;
                }
            }

            vertices.erase( vertices.begin() + erase_position );

        }
    }

    return vertices;
}

Solution GeneticAlgorithm::find_best( vector< Solution > population ){
    int position_best = 0;
    double fitness_best = population[ 0 ].get_fitness();
    double actual_fitness = 0.0;

    for( unsigned int i = 0; i < population.size(); i++ ){
        actual_fitness = population[ i ].get_fitness();
        if( fitness_best < actual_fitness ){
            fitness_best = actual_fitness;
            position_best = i;
        }
    }

    return population[ position_best ];
}

Solution GeneticAlgorithm::execute(){
    Solution best;
    Solution actual;
    vector< Solution > population;
    vector< Solution > elite;
    vector< Solution > kids;
    
    srand( this->seed );

    population = this->create_population();

    cout << 0.0 << endl;
    
    for( int i = 0; i < this->iterations; i++ ){
        if( i % 100 == 0 ) cout << i << endl; 
        elite = this->selection->select( population );
        kids = this->crossover->realize_crossover( elite );
        kids = this->mutation->apply_mutation( kids );
        kids = this->apply_local_search( kids );

        population = this->replacement->realize_replacement( population, kids );
        actual = this->find_best( population );

        if( best.get_fitness() < actual.get_fitness() ){
            best = actual;
            cout << i << "-" << best.get_fitness() << endl;
        }
    }

    return best;
}