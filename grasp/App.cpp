#include "App.h"

#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "RandomGreedyGen_MinMax.h"
#include "LocalSearchWithOperators.h"
#include "ArgumentReader.h"
#include "Operator.h"
#include "OperatorBestAdd.h"
#include "OperatorBestSwap.h"
#include "OperatorExchange.h"
#include "OperatorRandomRemove.h"
#include "OperatorEmpty.h"
#include "Log.h"

#include <iostream>
#include <map>
#include <random>

using namespace std;

Operator * App::create_remove_operator(){
    string argument = this->argument_reader->getValue( "--removeOperator" );
    double percentage = stod( this->argument_reader->getValue( "--removePercentage" ) );
    if( argument == "r" ){
        return new OperatorRandomRemove( percentage );
    }
    throw runtime_error( "Remove Operator is invalid: " + argument );
}

Operator * App::create_shuffle_operator(){
    string argument = this->argument_reader->getValue( "--shuffleOperator" );
    if( argument == "e" ){
        return new OperatorExchange();
    }
    throw runtime_error( "Shuffle Operator is invalid: " + argument );
}

Operator * App::create_add_operator(){
    string argument = this->argument_reader->getValue( "--addOperator" );
    if( argument == "b" ){
        return new OperatorBestAdd();
    }
    throw runtime_error( "Create Operator is invalid: " + argument );
}

Operator * App::create_swap_operator(){
    return new OperatorBestSwap();
}

void App::initialize_timer(){
    this->initial_time = clock();
}

void App::create_seed(){
    random_device rd;
    this->seed = rd();
    // this->seed = stoi( this->argument_reader->getValue( "--seed" ) );
    Log::instance()->log( std::to_string( seed ) + ";", 1 );
}


void App::read_instance(){
    this->file = this->argument_reader->getValue( "--file" );
    InstanceReader ir( this->file );
    ir.read();
    Log::instance()->log( this->file + ";", 1 );
}

void App::create_solution_generator(){
    double alpha = stod( this->argument_reader->getValue( "--alpha" ) );
    double margin = stod( this->argument_reader->getValue( "--margin" ) );
    this->solution_generator = new RandomGreedyGen_MinMax( alpha, margin );
}

void App::create_operators(){
    this->operators.push_back( this->create_remove_operator() );
    this->operators.push_back( this->create_shuffle_operator() );
    this->operators.push_back( this->create_add_operator() );
    this->operators.push_back( this->create_swap_operator() );
}

void App::create_local_search(){
    this->local_search = new LocalSearchWithOperators( this->operators );
}

void App::create_and_execute_grasp(){
    int iterations = stoi( this->argument_reader->getValue("--iterations") );
    this->grasp = new GRASP( iterations, this->seed, this->solution_generator, this->local_search );
    this->sol = this->grasp->execute();
}

void App::finalize_timer(){
    this->final_time = clock();
	this->total_time = ( (this->final_time - this->initial_time) / (double) CLOCKS_PER_SEC ) * 1000;
}

void App::show_results(){
    Log * log = Log::instance();
    log->log( this->sol.to_string(), 2 );
    log->log( std::to_string( this->sol.get_objetive_function() ) + ";", 0 );
    log->log( std::to_string( this->total_time ) + ";", 0 );
    log->show();
}

App::App( ArgumentReader * ar ){
    this->argument_reader = ar;
    this->solution_generator = 0;
    this->local_search = 0;
    this->grasp = 0;
    this->initial_time = 0;
    this->final_time = 0;
}

void App::execute(){
    this->initialize_timer();
    this->create_seed();
    this->read_instance();
    this->create_solution_generator();
    this->create_operators();
    this->create_local_search();
    this->create_and_execute_grasp();
    this->finalize_timer();
    this->show_results();
}
