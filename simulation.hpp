#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "Cinema.hpp"
#include "row.hpp"
#include "ticket.hpp"
#include "logger.h"
#include "manager.hpp"
#include "booking_clerk.hpp"
#include "bar_worker.hpp"
#include "doorman.hpp"
#include "employee_list.hpp"

class Simulation {
public:
    Simulation(std::vector<Cinema> cinemas, int duration);

    void run(std::string output_path);
    void start(int day, Logger& logger);
    void stop(Logger& logger);
    
private:
    std::vector<Cinema> cinemas;
    int duration;

    void generate_programme(Cinema& cinema, Logger& logger);
    Film generate_random_film();
    Showing generate_random_showing(std::chrono::system_clock::time_point start_time);
    Day generate_random_day();
    int generate_random_number(int min, int max);
    
    void generate_customers(Cinema& cinema, Logger& logger);
    void generate_duty_rota(Logger& logger); 
    void assign_customers_to_showings_and_choose_row(Cinema& cinema, Logger& logger);
    void generate_ticket(Cinema& cinema, Customer& customer, Showing& showing, Row row, Logger& logger);
    std::string generate_tasks(const std::vector<std::string>& tasks);
    
    std::string generate_random_name();
    std::string generate_random_surname();
    unsigned int generate_random_age();
    Gender generate_random_gender();
    unsigned int generate_random_salary();

    void generate_counters(Cinema& cinema, Logger& logger, BookingClerk& clerk);

    Manager generate_manager(Cinema& cinema, Logger& logger);
    Doorman generate_doorman(Cinema& cinema, Logger& logger);
    std::vector<BookingClerk> generate_booking_clerks(int count, Cinema& cinema, Logger& logger);
    std::vector<BarWorker> generate_bar_workers(int count, Cinema& cinema, Logger& logger);

};


#endif 
