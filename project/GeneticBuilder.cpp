#include "GeneticBuilder.h"
#include "RandomGreedyGen_MinMax.h"
#include "ProbabilisticSelection.h"
#include "SimpleCrossOver.h"
#include "RandomSwap.h"
#include "LocalSearchWithOperators.h"
#include "OperatorRandomRemove.h"
#include "OperatorExchange.h"
#include "OperatorBestSwap.h"
#include "OperatorBestAdd.h"
#include "BinaryTournament.h"

GeneticBuilder::GeneticBuilder( int seed, ArgumentReader * argument_reader ){
    this->seed = seed;
    this->argument_reader = argument_reader;
}

Operator * GeneticBuilder::create_remove_operator(){
    double percentage = stod( this->argument_reader->getValue( ARG_REMOVE_PERCENTAGE ) );
    return new OperatorRandomRemove( percentage );
}

Operator * GeneticBuilder::create_shuffle_operator(){
    return new OperatorExchange();
}

Operator * GeneticBuilder::create_add_operator(){
    return new OperatorBestAdd();
}

Operator * GeneticBuilder::create_swap_operator(){
    return new OperatorBestSwap();
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

LocalSearch * GeneticBuilder::create_local_search(){
    vector< Operator * > operators;
    operators.push_back( this->create_remove_operator() );
    operators.push_back( this->create_shuffle_operator() );
    operators.push_back( this->create_add_operator() );
    operators.push_back( this->create_swap_operator() );
    LocalSearch * ls = new LocalSearchWithOperators( operators );
    return ls;
}

Replacement * GeneticBuilder::create_replacement(){
    return new BinaryTournament();
}

GeneticAlgorithm GeneticBuilder::create(){
    int iterations = stoi( this->argument_reader->getValue( ARG_ITERATIONS ) );
    int population_size = stoi( this->argument_reader->getValue( ARG_POPULATION_SIZE ) );
    GeneticAlgorithm ga(
        this->seed, iterations, population_size, 
        this->create_solution_generator(), 
        this->create_selection(),
        this->create_crossover(),
        this->create_mutation(),
        this->create_local_search(),
        this->create_replacement()
    );
    return ga;
}