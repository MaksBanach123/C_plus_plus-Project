#include <iostream>
#include <string>
#include "ticket.hpp"
#include <map>
#pragma once

class Counter{
    public:
        Counter(unsigned int counter_number);

        void add_ticket(unsigned int ticket_number, const Ticket& ticket);
        void remove_ticket(unsigned int ticket_number);
        void edit_row_number(unsigned int ticket_number, unsigned int row_number);
        const std::map<unsigned int, Ticket>& get_tickets() const;
        unsigned int get_counter_number() const;
        
    private:
        unsigned int counter_number_;
        std::map <unsigned int, Ticket> tickets_;
};

std::ostream& operator<<(std::ostream& os, const Counter& counter);