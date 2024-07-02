#include "employee_list.hpp"
#include "employee.hpp"
#include "bar_worker.hpp"
#include "booking_clerk.hpp"
#include "doorman.hpp"
#include "manager.hpp"


void EmployeeList::add_employee(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty)
{
    std::unique_ptr<Employee> added_employee= std::make_unique<Employee>(aName, aSurname, aAge, aGender, aSalary, aDuty);
    employees.push_back(std::move(added_employee));
}

void EmployeeList::add_bar_worker(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title)
{
    std::unique_ptr<BarWorker> added_bar_worker= std::make_unique<BarWorker>(aName, aSurname, aAge, aGender, aSalary, aDuty, aJob_title);
    employees.push_back(std::move(added_bar_worker));
}

void EmployeeList::add_booking_clerk(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title)
{
    std::unique_ptr<BookingClerk> added_booking_clerk= std::make_unique<BookingClerk>(aName, aSurname, aAge, aGender, aSalary, aDuty, aJob_title);
    employees.push_back(std::move(added_booking_clerk));
}

void EmployeeList::add_doorman(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title)
{
    std::unique_ptr<Doorman> added_doorman= std::make_unique<Doorman>(aName, aSurname, aAge, aGender, aSalary, aDuty, aJob_title);
    employees.push_back(std::move(added_doorman));   
}

void EmployeeList::add_manager(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title)
{
    std::unique_ptr<Manager> added_manager= std::make_unique<Manager>(aName, aSurname, aAge, aGender, aSalary, aDuty, aJob_title);
    employees.push_back(std::move(added_manager)); 
}

unsigned EmployeeList::calculate_salary() const noexcept // ilustracja polimorfizmu
{
    return std::accumulate(employees.begin(), employees.end(), 0,
        [](const unsigned total_price_accumulator, const auto& emp_ptr){ return total_price_accumulator + emp_ptr -> calculate_salary(); });
}

const std::list<std::unique_ptr<Employee>>& EmployeeList::get_employees() const noexcept {
    return employees;
}

void EmployeeList::remove_employee(unsigned int index) {
    if (index < employees.size()) {
        auto it = employees.begin();
        std::advance(it, index);
        employees.erase(it);
    }
}
