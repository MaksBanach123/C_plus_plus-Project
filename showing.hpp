#ifndef SHOWING_HPP
#define SHOWING_HPP
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include "film.hpp"
#include "screening_room.hpp"


class Showing
{   
    private:
        Film film;
        ScreeningRoom screening_room;
        std::chrono::system_clock::time_point start_time;
        

    public:
        Showing(Film film, ScreeningRoom screening_room, std::chrono::system_clock::time_point start_time);

        Film get_film() const;
        ScreeningRoom get_screening_room() const;
        std::chrono::system_clock::time_point get_start_time() const;

        bool operator==(const Showing& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Showing& emp);

};

#endif
