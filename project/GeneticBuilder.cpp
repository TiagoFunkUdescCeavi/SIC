#include "GeneticBuilder.h"
#include "RandomGreedyGen_MinMax.h"
#include "ProbabilisticSelection.h"
#include "SimpleCrossOver.h"
#include "RandomSwap.h"
#include "BinaryTournament.h"

GeneticBuilder::GeneticBuilder( int seed, ArgumentReader * argument_reader ){
    this->seed = seed;
    this->argument_reader = argument_reader;
}

SolutionGeneration * GeneticBuilder::create_solution_generator(){
    double alpha = stod( this->argument_reader->getValue( ARG_ALPHA ) );
    double margin = stod( this->argument_reader->getValue( ARG_MARGIN ) );
    return new RandomGreedyGen_MinMax( alpha, margin );
}

Selection * GeneticBuilder::create_selection(){
    double rate = stod( this->argument_reader->getValue( ARG_RATE ) );
    return new ProbabilisticSelection( rate );
}

CrossOver * GeneticBuilder::create_crossover(){
    return new SimpleCrossOver();
}

Mutation * GeneticBuilder::create_mutation(){
    return new RandomSwap();
}

Replacement * GeneticBuilder::create_replacement(){
    return new BinaryTournament();
}

GeneticAlgorithm GeneticBuilder::create(){
    int iterations = stoi( this->argument_reader->getValue( ARG_ITERATIONS ) );
    int population_size = stoi( this->argument_reader->getValue( ARG_POPULATION_SIZE ) );
    GeneticAlgorithm ga( this->seed, iterations, population_size, this->create_solution_generator(), this->create_selection(), this->create_crossover(), this->create_mutation(), this->create_replacement() );
    return ga;
}