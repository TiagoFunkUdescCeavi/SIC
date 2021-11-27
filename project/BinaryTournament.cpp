#include "BinaryTournament.h"

#include "Utils.h"

vector< Solution > BinaryTournament::realize_replacement( vector< Solution > population, vector< Solution > kids ){
    double population_fitness = 0.0, kid_fitness = 0.0;

    for( unsigned int i = 0; i < kids.size(); i++ ){
        kid_fitness = kids[ i ].get_fitness();

        for( unsigned int j = 0; j < population.size(); j++ ){
            population_fitness = population[ j ].get_fitness();

            if( population_fitness < kid_fitness ){
                population[ j ] = kids[ i ];
                break;
            }
        }
    }

    return population;
}