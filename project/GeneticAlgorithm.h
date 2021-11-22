#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "Selection.h"

class GeneticAlgorithm{
    private:
        int seed;
        int iterations;
        int population_size;
        SolutionGeneration * solution_generator;
        Selection * selection;

        vector< Solution > create_population();
        int find_best( vector< Solution > population );

    public:
        GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator, Selection * selection );
        Solution execute();
};