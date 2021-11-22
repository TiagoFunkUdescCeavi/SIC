#ifndef PROBABILISTIC_SELECTION_H
#define PROBABILISTIC_SELECTION_H

#include "Selection.h"

class ProbabilisticSelection: public Selection{
    private:
        double rate;
        vector< Solution > population;
        vector< double > probabilities;

        void sort();
        double find_min_fitness();
        int find_solution( double random_number );
        double sum_fitness( double negative_fitness_correction );
        void calcule_probability( double sum_fitness );
        vector< Solution > select_elite( int size );

    public:
        ProbabilisticSelection( double rate );
        virtual vector< Solution > select( vector< Solution > population );
};

#endif