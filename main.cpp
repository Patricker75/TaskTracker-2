#include <iostream>
#include <sstream>
#include <fstream>

#include "CLI.h"

int main(int argc, char* argv []) {
    DataManager dm;

    Run(dm, "data.json");

    return 0;
}