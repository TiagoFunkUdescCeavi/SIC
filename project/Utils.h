#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Vertice.h"

using namespace std;

double * find_max_min( double * values, int size );
double calculate_mean( vector< double > values, int size );
double calculate_standard_deviation( vector< double > values, int size, double mean );
double calculate_score_z( double value, double mean, double stand );

double calculate_distance( Vertice * v1, Vertice * v2 );

template< typename T >
vector< T > shuffle( vector< T > list ){
    int n = 0;
    T aux;
    for( unsigned int i = 0; i < list.size(); i++ ){
        n = rand() % list.size();
        aux = list[ i ];
        list[ i ] = list[ n ];
        list[ n ] = aux;
    }
    return list;
}

int random_number( int max );
double random_number();

double calcule_percentage( int n, int total );

int truncate( double value, int decimals );

#endif