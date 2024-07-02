#ifndef FILM_HPP
#define FILM_HPP
#include <string>
#include <vector>
#include <iostream>
#include <chrono>


class Film
{   
    private:
        std::string title;
        std::string director;
        std::chrono::minutes duration;
        unsigned int minimum_age;
        

    public:
        Film(std::string title, std::string director, std::chrono::minutes duration, unsigned int minimum_age);

        std::string get_title() const;
        std::string get_director() const;
        std::chrono::minutes get_duration() const;
        unsigned int get_minimum_age() const;

        bool operator==(const Film& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Film& emp);

};

#endif
