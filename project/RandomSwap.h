#ifndef RANDOM_SWAP_H
#define RANDOM_SWAP_H

#include "Mutation.h"

class RandomSwap: public Mutation {
    private:
        Solution individual_mutation( Solution sol );
    public:
        virtual vector< Solution > apply_mutation( vector< Solution > population );
};

#endif