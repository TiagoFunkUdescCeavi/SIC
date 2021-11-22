#include "ProbabilisticSelection.h"
#include "Utils.h"

ProbabilisticSelection::ProbabilisticSelection( double rate ){
    this->rate = rate;
}

void ProbabilisticSelection::sort(){
    Solution sol;
    for( unsigned int i = 0; i < this->population.size(); i++ ){
        for( unsigned int j = 0; j < this->population.size(); j++ ){
            if( this->population[ i ].get_fitness() > this->population[ j ].get_fitness() ){
                sol = this->population[ i ];
                this->population[ i ] = this->population[ j ];
                this->population[ j ] = sol;
            }
        }
    }
}

double ProbabilisticSelection::find_min_fitness(){
    double actual_fitness = 0.0;
    double min_fitness = this->population[ 0 ].get_fitness();

    for( unsigned int i = 0; i < this->population.size(); i++ ){
        actual_fitness = population[ i ].get_fitness();
        if( min_fitness > actual_fitness ){
            min_fitness = actual_fitness;
        }
    }
    return min_fitness;
}

int ProbabilisticSelection::find_solution( double random_number ){
    int position = 0;
    for( unsigned int i = 0; i < this->probabilities.size(); i++ ){
        if( random_number < probabilities[ i ] ){
            position = i;
            break;
        }
    }
    return position;
}

double ProbabilisticSelection::sum_fitness( double negative_fitness_correction ){
    double sum = 0.0, value = 0.0;

    if( negative_fitness_correction < 0.0 ){
        negative_fitness_correction = negative_fitness_correction * -1 + 0.1;
    }else{
        negative_fitness_correction = 0.0;
    }
    
    for( unsigned int i = 0; i < this->population.size(); i++ ){
        value = this->population[ i ].get_fitness() + negative_fitness_correction;
        this->probabilities.push_back( value );
        sum += value;
    }

    return sum;
}

void ProbabilisticSelection::calcule_probability( double sum_fitness ){
    double value = 0.0, previous = 0.0;
    
    for( unsigned int i = 0; i < this->population.size(); i++ ){
        value = this->probabilities[ i ] / sum_fitness;
        value += previous;
        this->probabilities[ i ] = value;
        previous = value;
    }
}

vector< Solution > ProbabilisticSelection::select_elite( int size ){
    int position_selected = 0;
    double number = 0.0;
    vector< Solution > elite;

    for( int i = 0; i < size; i++ ){
        number = random_number();
        position_selected = this->find_solution( number );
        elite.push_back( this->population[ position_selected ] );
        this->population.erase( this->population.begin() + position_selected );
        this->probabilities.erase( this->probabilities.begin() + position_selected );
    }

    this->population.clear();
    this->probabilities.clear();

    return elite;
}

vector< Solution > ProbabilisticSelection::select( vector< Solution > population ){
    this->population = population;
    
    this->sort();
    double min_fitness = this->find_min_fitness();
    double sum = this->sum_fitness( min_fitness );
    this->calcule_probability( sum );

    int size = this->population.size() * this->rate;
    if( size % 2 == 1 ) size++;
    return this->select_elite( size );
}