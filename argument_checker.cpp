#include "argument_checker.hpp"

ArgumentChecker::ArgumentChecker(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Method of use: " << argv[0] << " <days_count> <txt_path>" << std::endl;
        std::exit(1);
    }
    else if (std::stoi(argv[1]) <= 0) {
        std::cerr << "The argument: " << argv[1] << " must be greater than 0 !!" << std::endl;
        std::exit(1);
    }
}