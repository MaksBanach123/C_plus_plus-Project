#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
#include <string>
#include <vector>
#include <iostream>

enum class Gender : unsigned int
{
    Male, Female
};

class Employee
{   
    protected:
        std::string name;
        std::string surname;
        unsigned int age;
        Gender gender;
        unsigned int salary;
        std::vector<std::string> duty;
        

    public:
        Employee(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty);
        
        virtual unsigned calculate_salary() const; // metoda wirtualna
        virtual ~Employee() = default;

        std::string get_name() const;
        std::string get_surname() const;
        unsigned int get_age() const;
        Gender get_gender() const;

        friend std::ostream& operator<<(std::ostream& os, const Employee& emp);

};

#endif
