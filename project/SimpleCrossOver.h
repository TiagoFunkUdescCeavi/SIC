#ifndef SIMPLE_CROSSOVER_H
#define SIMPLE_CROSSOVER_H

#include "CrossOver.h"

class SimpleCrossOver: public CrossOver{
    private:
        vector< Solution > shuffle_population( vector< Solution > elite_population );
        Solution generate_kid_with_even_paths( Solution dad, Solution mom );
        vector< Solution > individual_crossover_with_even_paths( Solution dad, Solution mom );
        vector< Solution > individual_crossover_with_odd_paths( Solution dad, Solution mom );

    public:
        virtual vector< Solution > realize_crossover( vector< Solution > elite_population );
};

#endif