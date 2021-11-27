#ifndef GENETIC_BUILDER_H
#define GENETIC_BUILDER_h

#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "GeneticAlgorithm.h"
#include "Selection.h"
#include "CrossOver.h"
#include "Mutation.h"
#include "Operator.h"
#include "Replacement.h"

class GeneticBuilder{
    private:
        int seed;
        ArgumentReader * argument_reader;

        Operator * create_remove_operator();
        Operator * create_shuffle_operator();
        Operator * create_add_operator();
        Operator * create_swap_operator();

        SolutionGeneration * create_solution_generator();
        Selection * create_selection();
        CrossOver * create_crossover();
        Mutation * create_mutation();
        LocalSearch * create_local_search();
        Replacement * create_replacement();

    public:
        GeneticBuilder( int seed, ArgumentReader * argument_reader );
        GeneticAlgorithm create();

};

#endif