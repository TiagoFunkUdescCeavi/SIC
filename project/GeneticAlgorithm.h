#include "ArgumentReader.h"
#include "SolutionGeneration.h"

class GeneticAlgorithm{
    private:
        int seed;
        SolutionGeneration * solution_generator;

    public:
        GeneticAlgorithm( int seed, SolutionGeneration * solution_generator );
        Solution execute();
};