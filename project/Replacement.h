#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "Solution.h"

class Replacement{
    public:
        virtual vector< Solution > realize_replacement( vector< Solution > population, vector< Solution > kids ) = 0;
};

#endif