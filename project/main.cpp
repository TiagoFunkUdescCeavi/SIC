#include "main.h"

#if DEBUG == true

#include "tests/test_solution.h"

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite_solution);
	MU_REPORT();
	return MU_EXIT_CODE;
}

#else

#include "App.h"
#include "ArgumentReader.h"

using namespace std;

int main( int argc, char * argv[] ){
    try {
        App * app = new App( new ArgumentReader( argc, argv ) );
        app->execute();
    }catch (exception &e){
        cerr << "**************************************************************************" << endl;
        cerr << e.what() << endl;
        cerr << "**************************************************************************" << endl;
    }
    return 0;
}

#endif