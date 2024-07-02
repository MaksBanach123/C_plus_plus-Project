#ifndef ARGUMENT_CHECKER_HPP
#define ARGUMENT_CHECKER_HPP

#include <iostream>
#include <string>

class ArgumentChecker {
public:
    ArgumentChecker(int argc, char* argv[]);

private:
    int argc_;
    char** argv_;
};

#endif