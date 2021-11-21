#ifndef APP_H
#define APP_H

#include <time.h>

#include "ArgumentReader.h"
#include "Solution.h"

class App{
    private:
        int seed;
        string file;
        clock_t initial_time;
        clock_t final_time;
        clock_t total_time;

        ArgumentReader * argument_reader;
        Solution sol;

        void initialize_timer();
        void create_seed();
        void read_instance();
        void create_and_execute_algorithm();
        void finalize_timer();
        void show_results();

    public:
        App( ArgumentReader * ar );
        void execute();
};

#endif