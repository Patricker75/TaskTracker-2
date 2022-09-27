#include <iostream>
#include <sstream>
#include <fstream>

#include "CLI.h"

int main(int argc, char* argv []) {
    DataManager dm;

    Run(dm, "test.json");

    return 0;
}