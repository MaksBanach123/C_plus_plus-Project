#include "ticket.hpp"

Ticket::Ticket(float price, std::string showing_title, std::chrono::system_clock::time_point showing_date, unsigned int row_number):
price_(price), showing_title_(std::move(showing_title)), showing_date_(std::move(showing_date)), row_number_(row_number){};

float Ticket::get_price() const{
    return price_;
}
std::string Ticket::get_showing_title() const{
    return showing_title_;
}
std::chrono::system_clock::time_point Ticket::get_showing_date() const{
    return showing_date_;
}
unsigned int Ticket::get_row_number() const{
    return row_number_;
}

void Ticket::set_price(float price) {
    price_ = price;
}

void Ticket::set_showing_title(const std::string& showing_title) {
    showing_title_ = showing_title;
}

void Ticket::set_showing_date(const std::chrono::system_clock::time_point& showing_date) {
    showing_date_ = showing_date;
}

void Ticket::set_row_number(unsigned int row_number) {
    row_number_ = row_number;
}

Ticket Ticket::get_ticket_data() const{
    return Ticket(price_, showing_title_, showing_date_, row_number_);
}

void Ticket::show_data(Ticket& ticket, Logger& logger) const{
    std::time_t time = std::chrono::system_clock::to_time_t(ticket.get_showing_date());
    std::tm* tm_ptr = std::localtime(&time);
    logger << " -----------TICKET-------------\n";
    logger << "Price: " << ticket.get_price() << "\n";
    logger << "Title: " << ticket.get_showing_title() << "\n";
    logger << "Date: " << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S") << "\n";
    logger << "Row: " << ticket.get_row_number() << "\n";
    logger << "--------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& time_point) {
    // Przekonwertowanie std::chrono::system_clock::time_point na std::time_t
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);
   // Użycie std::strftime do formatowania czasu jako std::string
    char buffer[20]; // Bufor na sformatowany czas
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    // Wyświetlenie czasu w formacie YYYY-MM-DD HH:MM:SS
    os << buffer;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "Price: " << ticket.get_price() << ", Showing Title: " << ticket.get_showing_title()
       << ", Showing Date: " << ticket.get_showing_date()
       << ", Row Number: " << ticket.get_row_number() << ", Seat Number: ";
    return os;
}
