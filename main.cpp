#include "src/interpreter.h"

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    string in;

    if (argc > 1) {
        if (!strcmp(argv[1], "--arquivo")){
            in = argv[2];
        }
    } else {
        in = "cin";
    }

    interpreter inter(in);
    inter.exec();
    return 0;
    
}

