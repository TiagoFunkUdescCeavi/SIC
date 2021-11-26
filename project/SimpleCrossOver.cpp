#include "SimpleCrossOver.h"
#include "Instance.h"
#include "Utils.h"

vector< Solution > SimpleCrossOver::shuffle_population( vector< Solution > elite_population ){
    int number = 0;
    unsigned int size = elite_population.size();
    Solution aux;

    for( unsigned int i = 0; i < size; i++ ){
        number = random_number();
        aux = elite_population[ i ];
        elite_population[ i ] = elite_population[ number ];
        elite_population[ number ] = aux;
    }

    return elite_population;
}

Solution SimpleCrossOver::generate_kid_with_even_paths( Solution dad, Solution mom ){
    Instance * inst = Instance::instance();
    int paths = inst->get_number_of_paths();
    int half_path = paths / 2;

    Solution kid( paths, inst->get_time_per_path() );
    for( int i = 0; i < paths; i++ ){
        kid.add_initial_and_final_vertice( i, inst->get_initial_vertice(), inst->get_final_vertice() );
    }
    for( int i = 0; i < half_path; i++ ){
        for( int j = 1; j < dad.get_length_of_path( i ) - 1; j++ ){
            kid.add( i, dad.get_vertice_in_path( i, j ) );
        }
    }
    for( int i = half_path; i < paths; i++ ){
        for( int j = 1; j < mom.get_length_of_path( i ) - 1; j++ ){
            kid.add( i, mom.get_vertice_in_path( i, j ) );
        }
    }

    return kid;
}

vector< Solution > SimpleCrossOver::individual_crossover_with_even_paths( Solution dad, Solution mom ){
    vector< Solution > kids;
    kids.push_back( this->generate_kid_with_even_paths( dad, mom ) );
    kids.push_back( this->generate_kid_with_even_paths( mom, dad ) );
    return kids;
}

vector< Solution > SimpleCrossOver::individual_crossover_with_odd_paths( Solution dad, Solution mom ){
    vector< Solution > kids;
    kids.push_back( dad );
    kids.push_back( mom );
    return kids;
}

vector< Solution > SimpleCrossOver::realize_crossover( vector< Solution > elite_population ){
    if( elite_population.size() % 2 == 1 ){
        throw runtime_error("Elite population have odd members on crossover phase.\n");
    }
    bool is_even = Instance::instance()->get_number_of_paths() % 2 == 0;
    vector< Solution > new_elite_population;
    vector< Solution > kids;
    elite_population = this->shuffle_population( elite_population );
    
    for( unsigned int i = 0; i < elite_population.size(); i += 2 ){
        if( is_even ){
            kids = this->individual_crossover_with_even_paths( elite_population[ i ], elite_population[ i+1 ] );
        }else{
            kids = this->individual_crossover_with_odd_paths( elite_population[ i ], elite_population[ i+1 ] );
        }
        new_elite_population.push_back( kids[ 0 ] );
        new_elite_population.push_back( kids[ 1 ] );
        kids.clear();
    }

    return new_elite_population;
}