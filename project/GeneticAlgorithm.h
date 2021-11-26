#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "Selection.h"
#include "CrossOver.h"

class GeneticAlgorithm{
    private:
        int seed;
        int iterations;
        int population_size;
        SolutionGeneration * solution_generator;
        Selection * selection;
        CrossOver * crossover;

        vector< Solution > create_population();
        Solution find_best( vector< Solution > population );

    public:
        GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator, Selection * selection, CrossOver * crossover );
        Solution execute();
};