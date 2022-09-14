#include <iostream>
#include <sstream>
#include <fstream>

#include "CLI.h"

int main(int argc, char* argv []) {
    Task t1("test one", 20220103);
    Task t2("test two", 20220103);
    Task t3("test three", 20220103);
    Task t4("test four", 20000101);
    Task t5("test five", 20020304);

    DataManager dm;

    dm.AddTask(t1);
    dm.AddTask(t2);
    dm.AddTask(t3);
    dm.AddTask(t4);
    dm.AddTask(t5);

    // std::ifstream input("TestCase1.txt");
    // std::cin.rdbuf(input.rdbuf());

    Run(dm);

    while (true) {}
    return 0;
}
