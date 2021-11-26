#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "Selection.h"
#include "CrossOver.h"
#include "Mutation.h"
#include "Replacement.h"

class GeneticAlgorithm{
    private:
        int seed;
        int iterations;
        int population_size;
        SolutionGeneration * solution_generator;
        Selection * selection;
        CrossOver * crossover;
        Mutation * mutation;
        Replacement * replacement;

        vector< Solution > create_population();
        Solution find_best( vector< Solution > population );

    public:
        GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator, Selection * selection, CrossOver * crossover, Mutation * mutation, Replacement * replacement );
        Solution execute();
};