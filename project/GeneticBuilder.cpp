#include "GeneticBuilder.h"
#include "RandomGreedyGen_MinMax.h"

GeneticBuilder::GeneticBuilder( int seed, ArgumentReader * argument_reader ){
    this->seed = seed;
    this->argument_reader = argument_reader;
}

SolutionGeneration * GeneticBuilder::create_solution_generator(){
    double alpha = stod( this->argument_reader->getValue( ARG_ALPHA ) );
    double margin = stod( this->argument_reader->getValue( ARG_MARGIN ) );
    return new RandomGreedyGen_MinMax( alpha, margin );
}

GeneticAlgorithm GeneticBuilder::create(){
    GeneticAlgorithm ga( this->seed, this->create_solution_generator() );
    return ga;
}