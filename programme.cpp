#include "programme.hpp"
#include <algorithm>

Programme::Programme(std::vector<Showing> showings, Day day): showings(showings), day(day)
{}

void Programme::add_showing(const Showing &new_showing)
{
    auto collision_check = [&](const Showing& existing_showing) {
        return (new_showing.get_start_time() < existing_showing.get_start_time() + existing_showing.get_film().get_duration());
    };
    if(std::any_of(showings.begin(), showings.end(), collision_check)) {
        throw std::invalid_argument("Collision detected: New showing overlaps with existing showing");
    }
    showings.push_back(new_showing);
}

void Programme::remove_showing(const Showing &film_to_remove)
{
    auto it = std::remove_if(showings.begin(), showings.end(), 
    [&](const Showing& showing) {
        return showing.get_film().get_title() == film_to_remove.get_film().get_title() &&
               showing.get_start_time() == film_to_remove.get_start_time();
    });

    if (it != showings.end()) {
        showings.erase(it, showings.end());
    } else {
        throw std::invalid_argument("Film not found in the programme");
    }
}

void Programme::edit_showing(const Showing &old_showing_data, const Showing &new_showing_data)
{
    auto new_showing = std::find(showings.begin(), showings.end(), new_showing_data);
    if (new_showing != showings.end()) {
        throw std::invalid_argument("Attempt to create a duplicated showing during edition of showing data");
    }  
    std::replace(showings.begin(), showings.end(), old_showing_data, new_showing_data);

}

std::vector<Showing> Programme::get_showing() const
{
    return showings;
}

Day Programme::get_day() const
{
    return day;
}

std::ostream &operator<<(std::ostream &os, const Programme &emp)
{
    for (const auto& showing : emp.get_showing()) {
        os << showing << std::endl;
    }

    return os;
}
