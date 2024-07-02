#include "film.hpp"

Film::Film(std::string title, std::string director, std::chrono::minutes duration, unsigned int minimum_age): 
title(title), director(director), duration(duration), minimum_age(minimum_age){}

std::string Film::get_title() const
{
    return title;
}

std::string Film::get_director() const
{
    return director;
}

std::chrono::minutes Film::get_duration() const
{
    return duration;
}

unsigned int Film::get_minimum_age() const
{
    return minimum_age;
}

bool Film::operator==(const Film &other) const
{
    return (title == other.title) && (director == other.director);
}

std::ostream &operator<<(std::ostream &os, const Film &emp)
{   
    os << "__Film details__" << std::endl;
    os << "Title: " << emp.get_title() << std::endl;
    os << "Director: " << emp.get_director() << std::endl;
    os << "Minimum age: " << emp.get_minimum_age() << std::endl;
    os << "Duration time: " << emp.get_duration().count() << " minutes" <<std::endl;
    return os;
}
