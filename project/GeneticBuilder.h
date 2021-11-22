#ifndef GENETIC_BUILDER_H
#define GENETIC_BUILDER_h

#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "GeneticAlgorithm.h"
#include "Selection.h"

class GeneticBuilder{
    private:
        int seed;
        ArgumentReader * argument_reader;

        SolutionGeneration * create_solution_generator();
        Selection * create_selection();

    public:
        GeneticBuilder( int seed, ArgumentReader * argument_reader );
        GeneticAlgorithm create();

};

#endif