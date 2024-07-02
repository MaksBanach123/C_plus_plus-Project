#include "doorman.hpp"
#include <random>
#include "non_positive_salary_exception.hpp"

Doorman::Doorman(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title) :
Employee{aName, aSurname, aAge, aGender, aSalary, aDuty},
job_title{aJob_title}
{}

unsigned int Doorman::get_salary() const
{
    return salary;
}

std::vector<std::string> Doorman::get_duty() const
{
    return duty;
}

std::string Doorman::get_job_title() const
{
    return job_title;
}

unsigned Doorman::calculate_salary() const
{
    unsigned doorman_salary = 0.9 * salary;
    if(doorman_salary == 0)
    {
        throw NonPositiveSalaryException();
    }
    return doorman_salary;
}
