#ifndef CINEMA_HPP
#define CINEMA_HPP
#include <string>
#include <vector>
#include <queue>
#include <random>
#include "programme.hpp"
#include "counter.hpp"
#include "customer.hpp"
#include "employee.hpp"

class Cinema
{
    private:
        std::string name;
        std::string address;
        std::vector<ScreeningRoom> screening_rooms;
        std::vector<Programme> programmes;
        std::vector<Counter> counters;
        std::queue<Customer> customers;
        std::vector<Employee> employees;



    public:
        Cinema(
            std::string name, std::string address, std::vector<ScreeningRoom> screening_rooms,
            std::vector<Programme> programmes, std::vector<Counter> counters, std::queue<Customer> customers, std::vector<Employee> employees
            );

        std::string get_name() const;
        std::string get_address() const;
        std::vector<ScreeningRoom> get_screening_rooms() const;
        std::vector<Programme> get_programmes() const;
        Programme& get_programme(unsigned int index);
        std::vector<Counter> get_counters() const;
        unsigned int get_random_counter() const;
        std::queue<Customer>& get_customers();
        std::vector<Employee>& get_employees();

        void add_programme(Programme& programme);
        void add_customer(Customer& customer);
        void add_employee(Employee &employee);
        void add_counter(Counter& counter);
        static Cinema load_from_file(const std::string& filename);
    
    friend std::ostream& operator<<(std::ostream& os, const Cinema& cinema);
};

#endif