#ifndef EMPLOYEE_LIST_HPP
#define EMPLOYEE_LIST_HPP
#include "employee.hpp"
#include "Cinema.hpp"
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>
#include <numeric>


class EmployeeList
{
    private:
        std::list<std::unique_ptr<Employee>> employees;
    public:
        void add_employee(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty);
        void add_bar_worker(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);
        void add_booking_clerk(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);
        void add_doorman(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);
        void add_manager(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);
        unsigned calculate_salary() const noexcept; 

        const std::list<std::unique_ptr<Employee>>& get_employees() const noexcept; 
        void remove_employee(unsigned int index); 

};

#endif