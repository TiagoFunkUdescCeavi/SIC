#include "BinaryTournament.h"

#include "Utils.h"

vector< Solution > BinaryTournament::realize_replacement( vector< Solution > population, vector< Solution > kids ){
    population = shuffle( population );
    kids = shuffle( kids );
    int population_fitness = 0, kid_fitness = 0;
    vector< Solution > new_population;

    for( unsigned int i = 0; i < population.size(); i++ ){
        if( i < kids.size() ){
            population_fitness = population[ i ].get_fitness();
            kid_fitness = kids[ i ].get_fitness();

            if( population_fitness > kid_fitness ){
                new_population.push_back( population[ i ] );
            }else{
                new_population.push_back( population[ i ] );
            }
        }else{
            new_population.push_back( population[ i ] );
        }
    }

    return new_population;
}