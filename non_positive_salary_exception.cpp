#include "non_positive_salary_exception.hpp"

NonPositiveSalaryException::NonPositiveSalaryException() :
std::invalid_argument{"Salary can't be less than zero!!"}
{}