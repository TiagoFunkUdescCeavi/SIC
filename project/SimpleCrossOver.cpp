#include "SimpleCrossOver.h"
#include "Instance.h"
#include "Utils.h"

Solution SimpleCrossOver::create_empty_solution(){
    Instance * inst = Instance::instance();
    int paths = inst->get_number_of_paths();

    Solution sol( paths, inst->get_time_per_path() );
    for( int i = 0; i < paths; i++ ){
        sol.add_initial_and_final_vertice( i, inst->get_initial_vertice(), inst->get_final_vertice() );
    }
    return sol;
}

vector< Vertice * > SimpleCrossOver::get_vertices_from_solution( Solution sol ){
    vector< Vertice * > vertices;

    for( int i = 0; i < sol.get_number_paths(); i++ ){
        for( int j = 1; j < sol.get_length_of_path( i ) - 1; j++ ){
            vertices.push_back( sol.get_vertice_in_path( i, j ) );
        }
        vertices.push_back( 0 );
    }

    return vertices;
}

Solution SimpleCrossOver::copy_vertices_to_solution( Solution sol, vector< Vertice * > vertices, int begin, int end ){
    Vertice * v = 0;
    for( int i = begin; i < end; i++ ){
        v = vertices[ i ];
        if( v == 0 ){
            this->last_path_used_in_solution++;
        }else{
            sol.add( this->last_path_used_in_solution, v );
        }
    }
    return sol;
}

Solution SimpleCrossOver::generate_kid( Solution dad, Solution mom ){
    vector< Vertice * > dad_paths = this->get_vertices_from_solution( dad );
    vector< Vertice * > mom_paths = this->get_vertices_from_solution( mom );

    Solution kid = this->create_empty_solution();

    int number = random_number( dad_paths.size() );

    this->last_path_used_in_solution = 0;
    kid = this->copy_vertices_to_solution( kid, dad_paths, 0, number );
    kid = this->copy_vertices_to_solution( kid, mom_paths, number, mom_paths.size() );

    return kid;
}

vector< Solution > SimpleCrossOver::individual_crossover( Solution dad, Solution mom ){
    vector< Solution > kids;
    kids.push_back( this->generate_kid( dad, mom ) );
    kids.push_back( this->generate_kid( mom, dad ) );
    return kids;
}

SimpleCrossOver::SimpleCrossOver(){
    this->last_path_used_in_solution = 0;
}

vector< Solution > SimpleCrossOver::realize_crossover( vector< Solution > elite_population ){
    if( elite_population.size() % 2 == 1 ){
        throw runtime_error("Elite population have odd members on crossover phase.\n");
    }
    vector< Solution > new_elite_population;
    vector< Solution > kids;
    elite_population = shuffle( elite_population );
    
    for( unsigned int i = 0; i < elite_population.size(); i += 2 ){
        kids = this->individual_crossover( elite_population[ i ], elite_population[ i+1 ] );
        new_elite_population.push_back( kids[ 0 ] );
        new_elite_population.push_back( kids[ 1 ] );
        kids.clear();
    }

    return new_elite_population;
}