#include "screening_room.hpp"
#include <algorithm>


ScreeningRoom::ScreeningRoom(unsigned int room_number): room_number_(room_number)
{}

 unsigned int ScreeningRoom::get_room_number() const{
    return room_number_;
 }
 
 const std::vector <Row>& ScreeningRoom::get_rows() const{
    return rows_;
 }

 Row& ScreeningRoom::get_row(unsigned int index){
    if (index < rows_.size()) {
        Row& row1 = rows_[index];
        return row1;
    } else {
        throw std::out_of_range("Index out of range");
    }
 }

void ScreeningRoom::remove_row(Row row1){
    auto it = std::find_if
    (rows_.begin(), rows_.end(), 
    [&row1](const Row& row2)
    {
        return row1.get_row_number() == row2.get_row_number();
    }
    );
    if (it != rows_.end()){
        rows_.erase(it);
    }
    else{
        throw std::invalid_argument("Attempt to delete non existing row!");
    }
}

void ScreeningRoom::add_row(Row row1){
    auto it = std::find_if
    (rows_.begin(), rows_.end(),
    [&row1](const Row& row2)
    {
        return row1.get_row_number() == row2.get_row_number();
    }
    );
    if (it != rows_.end()){
        throw std::invalid_argument("Attempt to add row with duplicated row number!");
    }
    else{
        rows_.push_back(row1);
    }
}

unsigned int ScreeningRoom::num_of_seats() const{
    unsigned int total_seats{0};
    for (const auto& row : rows_){
        total_seats += row.get_seats_count();
    }
    return total_seats;
}

void ScreeningRoom::add_rows(unsigned int num_rows, unsigned int num_seats_per_row)
{
    rows_.clear();

    for (unsigned int i = 1; i <= num_rows; ++i) {
        rows_.push_back(Row(i, num_seats_per_row));
    }
}

std::ostream& operator<<(std::ostream& os, const ScreeningRoom& screeningroom) {
    os << "Screening Room details:" << std::endl;
    os << "Room number: " << screeningroom.get_room_number() << std::endl;
    os << "Number of rows: " << screeningroom.get_rows().size() << std::endl;
    os << "Rows: " << std::endl;
    for (const auto& row : screeningroom.get_rows()){
        os << "Row number: " << row.get_row_number() << ", Number of seats: " << row.get_seats_count() << std::endl;
    }
    return os;
}
