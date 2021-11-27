#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "Selection.h"
#include "CrossOver.h"
#include "Mutation.h"
#include "LocalSearch.h"
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
        LocalSearch * local_search;
        Replacement * replacement;

        vector< Solution > create_population();
        vector< Solution > apply_local_search( vector< Solution > solution );
        vector< Vertice * > check_unused_vertices( Solution sol );
        Solution find_best( vector< Solution > population );

    public:
        GeneticAlgorithm( int seed, int iterations, int population_size, SolutionGeneration * solution_generator, Selection * selection, CrossOver * crossover, Mutation * mutation, LocalSearch * local_search, Replacement * replacement );
        Solution execute();
};