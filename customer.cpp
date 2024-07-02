#include "customer.hpp"


Customer::Customer(std::string name, std::string surname, unsigned int age, unsigned int phone_number, discount my_discount):
name_(std::move(name)), surname_(std::move(surname)), age_(std::move(age)), phone_number_(std::move(phone_number)), my_discount_(my_discount) {}

std::string Customer::get_name() const{
    return name_;
}
std::string Customer::get_surname() const{
    return surname_;
}
unsigned int Customer::get_age() const{
    return age_;
}
unsigned int Customer::get_phone_number() const{
    return phone_number_;
}
discount Customer::get_discount() const{
    return my_discount_;
}
Customer Customer::get_client_data() const {
    return Customer(name_, surname_, age_, phone_number_, my_discount_);
}

float Customer::if_discount() {
    float discount_value = 0;

    switch (my_discount_) {
        case discount::kid:
            if (age_ <= 12) {
                discount_value = 0.20; // 20% discount for kids
            }
            else {throw std::invalid_argument("Wrong discount!!");}
            break;

        case discount::student:
            if (age_ >= 13 && age_ <= 25) {
                discount_value = 0.10; // 10% discount for students
            }
            else {throw std::invalid_argument("Wrong discount!!");}
            break;

        case discount::senior:
            if (age_ >= 60) {
                discount_value = 0.30; // 30% discount for seniors
            }
            else {throw std::invalid_argument("Wrong discount!!");}
            break;

        case discount::no_discount:
            discount_value = 1; // No discount
            break;

        default:
            throw std::invalid_argument("Invalid discount type.");
            break;
    }

    return discount_value;
}

void Customer::set_age(unsigned int age){
    age_= age;
}

std::ostream& operator<<(std::ostream& os, const discount& discount) {
    switch (discount) {
        case discount::kid:
            os << "Kid";
            break;
        case discount::student:
            os << "Student";
            break;
        case discount::senior:
            os << "Senior";
            break;
        case discount::no_discount:
            os << "No discount";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, const Customer& customer){
    os << "Name: " << customer.get_name() << ", Surname: " <<
    customer.get_surname() << ", Age: " << customer.get_age() <<
    ", Phone number: " << customer.get_phone_number() << ", Discount: " 
    << customer.get_discount();
    return os;
}