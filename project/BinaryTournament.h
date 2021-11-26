#ifndef BINARY_TOURNAMENT_H
#define BINARY_TOURNAMENT_H

#include "Replacement.h"

class BinaryTournament: public Replacement {
    public:
        virtual vector< Solution > realize_replacement( vector< Solution > population, vector< Solution > kids );

};

#endif