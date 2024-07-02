#include <iostream>
#include <string>
#pragma once

enum class discount {
    kid=1, student, senior, no_discount
};

class Customer {
    public:
        Customer(std::string name, std::string surname, unsigned int age, unsigned int phone_number, discount my_discount);

        std::string get_name() const;
        std::string get_surname() const;
        unsigned int get_age() const;
        unsigned int get_phone_number() const;
        discount get_discount() const;
        Customer get_client_data() const;
        void set_age(unsigned int age);

        float if_discount();
        

    private:
        std::string name_;
        std::string surname_;
        unsigned int age_;
        unsigned int phone_number_;
        discount my_discount_;
};

std::ostream& operator<<(std::ostream& os, const discount& discount);
std::ostream& operator<<(std::ostream& os, const Customer& customer);