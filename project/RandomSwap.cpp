#include "RandomSwap.h"
#include "Utils.h"

Solution RandomSwap::individual_mutation( Solution sol ){
    vector< int > paths;
    for( int i = 0; i < sol.get_number_paths(); i++ ){
        if( !sol.is_empty( i ) ){
            paths.push_back( i );
        }
    }
    if( paths.size() < 2 ) return sol;
    paths = shuffle( paths );

    int first_path = paths[ 0 ];
    int first_position = random_number( sol.get_length_of_path( first_path ) - 2 ) + 1;
    int second_path = paths[ 1 ];
    int second_position = random_number( sol.get_length_of_path( second_path ) - 2 ) + 1;

    sol.swap( first_path, first_position, second_path, second_position );
    return sol;
}

vector< Solution > RandomSwap::apply_mutation( vector< Solution > population ){
    for( unsigned int i = 0; i < population.size(); i++ ){
        population[ i ] = this->individual_mutation( population[ i ] );
    }
    return population;
}