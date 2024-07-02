#include "row.hpp"

Row::Row(unsigned int row_number, unsigned int seats_count):
row_number_(row_number), seats_count_(seats_count){};

unsigned int Row::get_row_number() const{
    return row_number_;
}

unsigned int Row::get_seats_count() const{
    return seats_count_;
}

bool Row::assign_seat(){
    if (seats_count_ > 0) { 
        --seats_count_;
        return true;
    } 
    else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const Row& row) {
    os << "Row number: " << row.get_row_number() << "\n Seats count: " << row.get_seats_count();
    return os;
}