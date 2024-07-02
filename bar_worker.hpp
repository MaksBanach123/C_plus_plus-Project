#ifndef BAR_WORKER_HPP
#define BAR_WORKER_HPP
#include "employee.hpp"
#include <ranges>

class BarWorker : public Employee
{
    private:
        std::string job_title;

    public:
        BarWorker(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);

        unsigned int get_salary() const;
        std::vector<std::string> get_duty() const;
        std::string get_job_title() const;
        unsigned calculate_salary() const override; 
};

#endif