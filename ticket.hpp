#include <iostream>
#include <string>
#include <chrono>
#include "logger.h"
#include <iomanip>
#pragma once


class Ticket{
    public:
        Ticket() = default;
        Ticket(float price, std::string showing_title, std::chrono::system_clock::time_point showing_date, unsigned int row_number);

        float get_price() const;
        std::string get_showing_title() const;
        std::chrono::system_clock::time_point get_showing_date() const;
        unsigned int get_row_number() const;
        
        void set_price(float price);
        void set_showing_title(const std::string& showing_title);
        void set_showing_date(const std::chrono::system_clock::time_point& showing_date);
        void set_row_number(unsigned int row_number);
        
        Ticket get_ticket_data() const;
        void show_data(Ticket& ticket, Logger& logger) const;
    private:
        float price_;
        std::string showing_title_;
        std::chrono::system_clock::time_point showing_date_;
        unsigned int row_number_;
};

std::ostream& operator<<(std::ostream& os, const Ticket& ticket);