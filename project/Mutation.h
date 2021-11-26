#ifndef MUTATION_H
#define MUTATION_H

#include "Solution.h"

class Mutation{
    public:
        virtual vector< Solution > apply_mutation( vector< Solution > population ) = 0;
};

#endif