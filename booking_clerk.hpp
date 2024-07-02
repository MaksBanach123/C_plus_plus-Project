#ifndef BOOKING_CLERK_HPP
#define BOOKING_CLERK_HPP
#include "employee.hpp"
#include <ranges>

class BookingClerk : public Employee
{
    private:
        std::string job_title;

    public:
        BookingClerk(std::string aName, std::string aSurname, unsigned int aAge, Gender aGender, unsigned int aSalary, std::vector<std::string> aDuty, std::string aJob_title);

        unsigned int get_salary() const;
        std::vector<std::string> get_duty() const;
        std::string get_job_title() const;
        unsigned calculate_salary() const override;
};

#endif