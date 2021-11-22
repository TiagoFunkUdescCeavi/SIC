#ifndef SELECTION_H
#define SELECTION_H

#include <vector>
#include "Solution.h"

class Selection{
    public:
        Selection(){}
        virtual vector< Solution > select( vector< Solution > population ) = 0;
};

#endif