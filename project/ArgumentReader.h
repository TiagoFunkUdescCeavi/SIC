#ifndef ARGUMENTSREADER_H_
#define ARGUMENTSREADER_H_

#include <string>
#include <vector>

using namespace std;

#define ARG_SEED						"--seed"
#define ARG_FILE 						"--file"

#define ARG_ALGORITHM 					"--algorithm"
#define ARG_ALGORITHM_GRASP				"grasp"
#define ARG_ALGORITHM_GENETIC			"genetic"

#define ARG_REMOVE_OPERATOR 			"--removeOperator"
#define ARG_REMOVE_OPERATOR_RANDOM		"random"
#define ARG_REMOVE_PERCENTAGE 			"--removePercentage"

#define ARG_SHUFFLE_OPERATOR 			"--shuffleOperator"
#define ARG_SHUFFLE_OPERATOR_EXCHANGE	"exchange"

#define ARG_ADD_OPERATOR 				"--addOperator"
#define ARG_ADD_OPERATOR_BEST	 		"best"

#define ARG_ALPHA 						"--alpha"
#define ARG_MARGIN 						"--margin"
#define ARG_ITERATIONS 					"--iterations"
#define ARG_POPULATION_SIZE				"--populationSize"
#define ARG_RATE						"--rate"

struct Argument{
	string name;
	string value;
};

class ArgumentReader{
private:
	vector< Argument > arguments;

	void process( vector< string > args );

public:
	ArgumentReader( int argc, char* argv[] );
	string getValue( string name );
};

#endif /* ARGUMENTSREADER_H_ */