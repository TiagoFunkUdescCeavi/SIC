#define IRACE_CONSTANT -1

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