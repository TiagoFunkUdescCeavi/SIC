#ifndef GRASP_BUILDER_H
#define GRASP_BUILDER_H

#include "SolutionGeneration.h"
#include "Operator.h"
#include "LocalSearch.h"
#include "Grasp.h"
#include "ArgumentReader.h"

class GraspBuilder{
    private:
        int seed;
        ArgumentReader * argument_reader;
        SolutionGeneration * solution_generator;
        vector< Operator * > operators;
        LocalSearch * local_search;

        Operator * create_remove_operator();
        Operator * create_shuffle_operator();
        Operator * create_add_operator();
        Operator * create_swap_operator();

        void create_solution_generator();
        void create_operators();
        void create_local_search();
    
    public:
        GraspBuilder( int seed, ArgumentReader * argument_reader );
        GRASP create();
};

#endif