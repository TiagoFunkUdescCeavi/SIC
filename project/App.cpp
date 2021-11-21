#include "App.h"

#include "InstanceReader.h"
#include "Instance.h"
#include "ArgumentReader.h"
#include "Log.h"
#include "GraspBuilder.h"

#include <iostream>
#include <map>
#include <random>

using namespace std;

void App::initialize_timer(){
    this->initial_time = clock();
}

void App::create_seed(){
    random_device rd;
    this->seed = rd();
    // this->seed = stoi( this->argument_reader->getValue( ARG_SEED ) );
    Log::instance()->log( std::to_string( seed ) + ";", 1 );
}

void App::read_instance(){
    this->file = this->argument_reader->getValue( ARG_FILE );
    InstanceReader ir( this->file );
    ir.read();
    Log::instance()->log( this->file + ";", 1 );
}

void App::create_and_execute_algorithm(){
    if( this->argument_reader->getValue( ARG_ALGORITHM ) == ARG_ALGORITHM_GRASP ){
        GraspBuilder g( this->seed, this->argument_reader );
        this->sol = g.create().execute();
    }
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
    this->initial_time = 0;
    this->final_time = 0;
}

void App::execute(){
    this->initialize_timer();
    this->create_seed();
    this->read_instance();
    this->create_and_execute_algorithm();
    this->finalize_timer();
    this->show_results();
}
