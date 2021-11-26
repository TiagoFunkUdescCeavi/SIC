#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "Solution.h"
#include <vector>

class CrossOver {
    public:
        virtual vector< Solution > realize_crossover( vector< Solution > elite_population ) = 0;
};

#endif