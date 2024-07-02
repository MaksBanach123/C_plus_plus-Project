#include "bar_worker.hpp"
#include <random>
#include "non_positive_salary_exception.hpp"

BarWorker::BarWorker(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title) :
Employee{aName, aSurname, aAge, aGender, aSalary, aDuty}, // jawne wywolanie konstruktora klasy bazowej
job_title{aJob_title}
{}

unsigned int BarWorker::get_salary() const
{
    return salary;
}

std::vector<std::string> BarWorker::get_duty() const
{
    return duty;
}

std::string BarWorker::get_job_title() const
{
    return job_title;
}

unsigned BarWorker::calculate_salary() const
{
    unsigned bar_worker_salary = 1.1 * salary;
    if(bar_worker_salary == 0)
    {
        throw NonPositiveSalaryException();
    }
    return bar_worker_salary;
}
