#include <iostream>
#include "row.hpp"
#include <vector>
#pragma once

class ScreeningRoom{
    public:
        ScreeningRoom(unsigned int room_number);        
        
        unsigned int get_room_number() const;
        const std::vector <Row>& get_rows() const;
        Row& get_row(unsigned int index);

        void remove_row(Row row1);
        void add_row(Row row1);
        unsigned int num_of_seats() const;
        void add_rows(unsigned int num_rows, unsigned int num_seats_per_row);

    private:
        unsigned int room_number_;
        std::vector <Row> rows_;
};

std::ostream& operator<<(std::ostream& os, const ScreeningRoom& screeningroom);