#ifndef ZERO_PRICE_EXCEPTION_HPP
#define ZERO_PRICE_EXCEPTION_HPP
#include <stdexcept>

class NonPositiveSalaryException : public std::invalid_argument
{
    public: 
        NonPositiveSalaryException();
};
#endif