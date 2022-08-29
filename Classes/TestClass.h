#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <string>

#include "KeyValuePair.h"

struct TestClass : KeyValuePair<int, std::string> {
    TestClass() {}

    TestClass(int key, std::string value) : KeyValuePair<int, std::string>(key, value) {}

    TestClass(const TestClass& obj) : KeyValuePair<int, std::string>(obj) {}
};

#endif