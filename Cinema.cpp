#include "Cinema.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>


Cinema::Cinema(std::string name, std::string address, std::vector<ScreeningRoom> screening_rooms, std::vector<Programme> programmes, std::vector<Counter> counters, std::queue<Customer> customers, std::vector<Employee> employees):
name{name}, address{address}, screening_rooms(screening_rooms), programmes(programmes), counters(counters), customers(customers), employees(employees)
{}

std::string Cinema::get_name() const
{
    return name;
}

std::string Cinema::get_address() const
{
    return address;
}

std::vector<ScreeningRoom> Cinema::get_screening_rooms() const
{
    return screening_rooms;
}

std::vector<Programme> Cinema::get_programmes() const
{
    return programmes;
}

Programme& Cinema::get_programme(unsigned int index){
    if (index >= 0 && index < programmes.size()) {
        return programmes[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

std::vector<Counter> Cinema::get_counters() const{
    return counters;
}

unsigned int Cinema::get_random_counter() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> counter_dist(0, counters.size() - 1);
    Counter counter = counters[counter_dist(gen)];
    return counter.get_counter_number();
}

std::queue<Customer>& Cinema::get_customers(){
    return customers;
}

std::vector<Employee>& Cinema::get_employees(){
    return employees;
}

void Cinema::add_programme(Programme &programme){
    // Sprawdzamy, czy taki program już istnieje w wektorze programów
    auto it = std::find_if(programmes.begin(), programmes.end(), [&](const Programme& p) {
        return p.get_day() == programme.get_day();
    });

    // Jeśli program nie istnieje, dodajemy go do wektora
    if (it == programmes.end()) {
        programmes.push_back(programme);
    } else {
        // Jeśli program już istnieje, możemy np. wyświetlić komunikat bądź podjąć inną akcję
        std::cout << "Program for day " << static_cast<int>(programme.get_day()) << " already exists." << std::endl;
    }
}

void Cinema::add_customer(Customer& customer)
{
    // Dodajemy klienta do kolejki
    customers.push(customer);
}

void Cinema::add_employee(Employee &employee)
{
    employees.push_back(employee);
}

void Cinema::add_counter(Counter& counter)
{
    counters.push_back(counter);
}

Cinema Cinema::load_from_file(const std::string &filename)
{
    std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Unable to open file: " + filename);
            }

            std::string name, address;
            std::vector<ScreeningRoom> screeningRooms;
            std::vector<Programme> programmes;
            std::vector<Counter> counters;
            std::queue<Customer> customers;
            std::vector<Employee> employees;
            std::string line;
            
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string attribute;
                std::getline(iss, attribute, ','); 

                if (attribute == "Name") {
                    std::getline(iss, name);
                } else if (attribute == "Address") {
                    std::getline(iss, address);
                }
            }

            return Cinema(name, address, screeningRooms, programmes, counters, customers, employees);
}

std::ostream &operator<<(std::ostream &os, const Cinema &cinema)
{
    os << "Cinema name: " << cinema.get_name() << std::endl;
    os << "Cinema address: " << cinema.get_address() << std::endl;
    return os;
}
