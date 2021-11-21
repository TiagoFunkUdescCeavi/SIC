#include "GraspBuilder.h"

#include "Operator.h"
#include "OperatorBestAdd.h"
#include "OperatorBestSwap.h"
#include "OperatorExchange.h"
#include "OperatorRandomRemove.h"
#include "OperatorEmpty.h"
#include "RandomGreedyGen_MinMax.h"
#include "LocalSearchWithOperators.h"

Operator * GraspBuilder::create_remove_operator(){
    string argument = this->argument_reader->getValue( ARG_REMOVE_OPERATOR );
    double percentage = stod( this->argument_reader->getValue( ARG_REMOVE_PERCENTAGE ) );
    if( argument == ARG_REMOVE_OPERATOR_RANDOM ){
        return new OperatorRandomRemove( percentage );
    }
    throw runtime_error( "Remove Operator is invalid: " + argument );
}

Operator * GraspBuilder::create_shuffle_operator(){
    string argument = this->argument_reader->getValue( ARG_SHUFFLE_OPERATOR );
    if( argument == ARG_SHUFFLE_OPERATOR_EXCHANGE ){
        return new OperatorExchange();
    }
    throw runtime_error( "Shuffle Operator is invalid: " + argument );
}

Operator * GraspBuilder::create_add_operator(){
    string argument = this->argument_reader->getValue( ARG_ADD_OPERATOR );
    if( argument == ARG_ADD_OPERATOR_BEST ){
        return new OperatorBestAdd();
    }
    throw runtime_error( "Create Operator is invalid: " + argument );
}

Operator * GraspBuilder::create_swap_operator(){
    return new OperatorBestSwap();
}

void GraspBuilder::create_solution_generator(){
    double alpha = stod( this->argument_reader->getValue( ARG_ALPHA ) );
    double margin = stod( this->argument_reader->getValue( ARG_MARGIN ) );
    this->solution_generator = new RandomGreedyGen_MinMax( alpha, margin );
}

void GraspBuilder::create_operators(){
    this->operators.push_back( this->create_remove_operator() );
    this->operators.push_back( this->create_shuffle_operator() );
    this->operators.push_back( this->create_add_operator() );
    this->operators.push_back( this->create_swap_operator() );
}

void GraspBuilder::create_local_search(){
    this->local_search = new LocalSearchWithOperators( this->operators );
}

GraspBuilder::GraspBuilder( int seed, ArgumentReader * argument_reader){
    this->seed = seed;
    this->argument_reader = argument_reader;
    this->solution_generator = 0;
    this->local_search = 0;
}

GRASP GraspBuilder::create(){
    this->create_solution_generator();
    this->create_operators();
    this->create_local_search();
    int iterations = stoi( this->argument_reader->getValue( ARG_ITERATIONS ) );
    GRASP grasp( iterations, this->seed, this->solution_generator, this->local_search );
    return grasp;
}