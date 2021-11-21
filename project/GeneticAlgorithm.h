#include "ArgumentReader.h"
#include "SolutionGeneration.h"

class GeneticAlgorithm{
    private:
        int seed;
        int iterations;
        int population_size;
        SolutionGeneration * solution_generator;

        vector< Solution > create_population();
        int find_best( vector< Solution > population );

    public:
        GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator );
        Solution execute();
};