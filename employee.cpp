#include "employee.hpp"
#include "non_positive_salary_exception.hpp"

Employee::Employee(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty) : 
name{aName}, surname{aSurname}, age{aAge}, gender{aGender}
{
    if(aSalary < 0)
    {
        throw NonPositiveSalaryException();
    } 
    
    salary = aSalary; 
}   

unsigned Employee::calculate_salary() const
{
    return salary;
}

std::string Employee::get_name() const
{
    return name;
}

std::string Employee::get_surname() const
{
    return surname;
}

unsigned int Employee::get_age() const
{
    return age;
}

Gender Employee::get_gender() const
{
    return gender;
}

std::ostream &operator<<(std::ostream &os, const Employee &emp)
{
    os << "Name: " << emp.get_name() << std::endl;
    os << "Surname: " << emp.get_surname() << std::endl;
    os << "Age: " << emp.get_age() << std::endl;
    os << "Gender: " << (emp.gender == Gender::Male ? "Male" : "Female") << std::endl;
    os << "Salary: " << emp.calculate_salary() << std::endl;
    return os;
}
