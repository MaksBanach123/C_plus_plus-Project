#include "manager.hpp"
#include <random>
#include "non_positive_salary_exception.hpp"

Manager::Manager(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title) :
Employee{aName, aSurname, aAge, aGender, aSalary, aDuty},
job_title{aJob_title}
{}

unsigned int Manager::get_salary() const
{
    return salary;
}

std::vector<std::string> Manager::get_duty() const
{
    return duty;
}

std::string Manager::get_job_title() const
{
    return job_title;
}

unsigned Manager::calculate_salary() const
{
    unsigned boking_clerk_salary = 2.0 * salary;
    if(boking_clerk_salary == 0)
    {
        throw NonPositiveSalaryException();
    }
    return boking_clerk_salary;
}
