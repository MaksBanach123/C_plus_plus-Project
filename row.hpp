#include <iostream>
#pragma once

class Row{
    public:
        Row(unsigned int row_number, unsigned int seats_count);

        unsigned int get_row_number() const;
        unsigned int get_seats_count() const;
        bool assign_seat();

    private:
        unsigned int row_number_;
        unsigned int seats_count_;
};
std::ostream& operator<<(std::ostream& os, const Row& row);