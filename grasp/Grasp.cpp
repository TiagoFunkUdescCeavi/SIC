#include "Grasp.h"
#include "Log.h"
#include "Utils.h"

GRASP::GRASP( int iterations, int seed, SolutionGeneration * solution_generation, LocalSearch * local_search ){
    this->iterations = iterations;
    this->seed = seed;
    this->solution_generation = solution_generation;
    this->local_search = local_search;
    this->previous_generate_solutions.resize( SOLUTION_HASH_SIZE );
}

Solution GRASP::generate(){
    this->unused_vertices.clear();
    Solution sol = this->solution_generation->random_greedy_generation( Instance::instance()->get_path_vertices() );
    sol.update_time_per_path( Instance::instance()->get_time_per_path() );
    this->unused_vertices = this->solution_generation->get_unused_vertices();
    return sol;
}

bool GRASP::is_acepted( Solution sol ){
    int h = sol.get_hash();
    if( !this->previous_generate_solutions.find( h ) ){
        this->previous_generate_solutions.insert( h );
        return true;
    }
    return false;
}

Solution GRASP::apply_local_search( Solution sol ){
    Solution actual = this->local_search->execute( sol, this->unused_vertices );
    this->unused_vertices = this->local_search->get_unused_vertices();
    return actual;
}

bool GRASP::is_better( Solution sol, Solution best ){
    return sol.get_objetive_function() > best.get_objetive_function();
}

Solution GRASP::execute(){
    Solution actual;
    Solution best;
    srand( this->seed );

    for (int i = 0; i < this->iterations; i++){        
        actual = this->generate();

        if( !is_acepted( actual ) ) continue;

        actual = this->apply_local_search( actual );

        if( this->is_better( actual, best ) ){
            best = actual;
            Log::instance()->log( std::to_string( i+1 ) + "-" + std::to_string( best.get_objetive_function() ) + ",", 1 );
        }
    }
    Log::instance()->log( ";", 1 );
    return best;
}