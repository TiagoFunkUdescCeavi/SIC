#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "GeneticAlgorithm.h"

class GeneticBuilder{
    private:
        int seed;
        ArgumentReader * argument_reader;

        SolutionGeneration * create_solution_generator();

    public:
        GeneticBuilder( int seed, ArgumentReader * argument_reader );
        GeneticAlgorithm create();

};