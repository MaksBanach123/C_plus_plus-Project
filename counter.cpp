
#include "counter.hpp"

Counter::Counter(unsigned int counter_number) : counter_number_(counter_number) {};

void Counter::add_ticket(unsigned int ticket_number, const Ticket& ticket) {
    if (tickets_.count(ticket_number) > 0) {
        throw std::invalid_argument("Ticket number already exists in the counter.");
    }
    tickets_[ticket_number] = ticket;
}

void Counter::remove_ticket(unsigned int ticket_number) {
    tickets_.erase(ticket_number);
}

void Counter::edit_row_number(unsigned int ticket_number, unsigned int new_row_number){
    auto it = tickets_.find(ticket_number);
    if (it != tickets_.end()){
        it -> second.set_row_number(new_row_number);
    } else {
        throw std::invalid_argument("Ticket not found!");
    }
}

unsigned int Counter::get_counter_number() const{
    return counter_number_;
}
        
const std::map<unsigned int, Ticket>& Counter::get_tickets() const {
    return tickets_;
}

std::ostream& operator<<(std::ostream& os, const Counter& counter) {
    os << "Tickets:" << std::endl;
    for (const auto& pair : counter.get_tickets()) {
        os << "Ticket number: " << pair.first << "\n Ticket details: \n" << pair.second.get_ticket_data() << std::endl;
    }
    return os;
}