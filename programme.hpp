#ifndef PROGRAMME_HPP
#define PROGRAMME_HPP
#include <string>
#include <vector>
#include <iostream>
#include "showing.hpp"


enum class Day : unsigned int
{
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday 
};

class Programme
{   
    private:
        std::vector<Showing> showings;
        Day day;
        

    public:
        Programme(std::vector<Showing> showings, Day day);

        std::vector<Showing> get_showing() const;
        Day get_day() const;

        void add_showing(const Showing& new_showing);
        void remove_showing(const Showing& film_to_remove);
        void edit_showing(const Showing& old_showing_data, const Showing& new_showing_data);
        
        friend std::ostream& operator<<(std::ostream& os, const Programme& emp);

};

#endif
