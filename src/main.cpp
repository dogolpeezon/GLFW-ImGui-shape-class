#include "../include/include.h"
#include "../include/window.h"
#include "../include/quads.h"
#include "../include/cube.h"
#include "../include/manager.h"

#include <iostream>

int main( int argc, const char *argv[] ){

    // Not sure which is the best way to inst the manager obj..
    // this way
    static Manager *man = NULL;
    if( man == NULL ){
        man = new Manager();
        man->run();
    }
    // or this way??
    // Manager man;
    // man.run();

    return 0;
}
