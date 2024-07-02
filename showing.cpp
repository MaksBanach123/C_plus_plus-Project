#include "showing.hpp"
#include <iomanip> 

Showing::Showing(Film film, ScreeningRoom screening_room, std::chrono::system_clock::time_point start_time):
film(film), screening_room(screening_room), start_time(start_time)
{}

Film Showing::get_film() const
{
    return film;
}

ScreeningRoom Showing::get_screening_room() const
{
    return screening_room;
}

std::chrono::system_clock::time_point Showing::get_start_time() const
{
    return start_time;
}

bool Showing::operator==(const Showing &other) const
{
    return (film == other.film) && (start_time == other.start_time);
}

std::ostream &operator<<(std::ostream &os, const Showing &emp)
{
    os << emp.get_film() << std::endl;
    auto time = std::chrono::system_clock::to_time_t(emp.get_start_time());
    os << "Start time: " << std::put_time(std::localtime(&time), "%H:%M:%S") << std::endl;
    os << "Screening room: " << emp.get_screening_room() << std::endl;
    return os;
}
