#ifndef SIMPLE_CROSSOVER_H
#define SIMPLE_CROSSOVER_H

#include "CrossOver.h"

class SimpleCrossOver: public CrossOver{
    private:
        int last_path_used_in_solution;

        Solution create_empty_solution();
        vector< Vertice * > get_vertices_from_solution( Solution sol );
        Solution copy_vertices_to_solution( Solution sol, vector< Vertice * > vertices, int begin, int end );

        Solution generate_kid( Solution dad, Solution mom );
        vector< Solution > individual_crossover( Solution dad, Solution mom );

    public:
        SimpleCrossOver();
        virtual vector< Solution > realize_crossover( vector< Solution > elite_population );
};

#endif