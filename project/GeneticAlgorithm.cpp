#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm( int seed, SolutionGeneration * solution_generator ){
    this->seed = seed;
    this->solution_generator = solution_generator;
}

Solution GeneticAlgorithm::execute(){
    Solution sol;
    return sol;
}