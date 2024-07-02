#include "simulation.hpp"



Simulation::Simulation(std::vector<Cinema> cinemas, int duration) : cinemas(cinemas), duration(duration) {}

void Simulation::run(std::string output_path)
{
    // Uruchomienie symulacji
    Logger logger(output_path);
    for (int i = 0; i < duration; ++i) {
        start(i, logger); // Rozpoczęcie symulacji
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Symulacja trwania dnia
        stop(logger);  // Zakończenie symulacji
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Symulacja przejścia do kolejnego dnia
    }
}

void Simulation::start(int day, Logger& logger)
{
    // Rozpoczęcie symulacji otwarcia kina
    logger << "\n\nDay " << day + 1 << " of the week. The cinema is opened. We invite you to watch the films!" << std::endl;

    // Generowanie repertuaru dla każdego kina
    for (Cinema& cinema : cinemas) {
        generate_programme(cinema, logger);
    }

    // Wyświetlanie repertuaru dla każdego kina
    for (const Cinema& cinema : cinemas) {
        logger << "   " << std::endl;
        logger << cinema.get_name() << " is proud to present to you its programme for today!" << std::endl;
        for (const Programme& programme : cinema.get_programmes()) {
            logger << " " << std::endl;
            logger << programme << std::endl;    
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // generowanie pracownikow
    for (Cinema& cinema : cinemas) {
        auto manager = generate_manager(cinema, logger);
        auto doorman = generate_doorman(cinema, logger);  
        auto clerks = generate_booking_clerks(2, cinema, logger); 
        auto bar_workers = generate_bar_workers(3, cinema, logger); 
        generate_duty_rota(logger);

        // Reprezentacja wykorzystania polimorfizmu
        EmployeeList employee_list;
        for (const auto& clerk : clerks) {
        employee_list.add_booking_clerk(clerk.get_name(), clerk.get_surname(), clerk.get_age(), clerk.get_gender(), clerk.get_salary(), clerk.get_duty(), clerk.get_job_title());
        }

        for (const auto& worker : bar_workers) {
            employee_list.add_bar_worker(worker.get_name(), worker.get_surname(), worker.get_age(), worker.get_gender(), worker.get_salary(), worker.get_duty(), worker.get_job_title());
        }
        employee_list.add_manager(manager.get_name(), manager.get_surname(), manager.get_age(), manager.get_gender(), manager.get_salary(), manager.get_duty(), manager.get_job_title());
        employee_list.add_doorman(doorman.get_name(), doorman.get_surname(), doorman.get_age(), doorman.get_gender(), doorman.get_salary(), doorman.get_duty(), doorman.get_job_title());

        unsigned total_salary = employee_list.calculate_salary();
        logger << "Total emplyees' salary: " << total_salary << "$" << " <- (Polimorphism usage)\n" << std::endl;
        }   
    

    std::this_thread::sleep_for(std::chrono::seconds(2));
    // Generowanie klientów
    for (Cinema& cinema : cinemas) {
        generate_customers(cinema, logger);
        assign_customers_to_showings_and_choose_row(cinema, logger);      
    }

}

void Simulation::stop(Logger& logger)
{
    // Zakończenie symulacji zamknięcia kina
    logger << "\nThe cinema is already closed. Thank you for your visit and welcome back!" << std::endl;
}

void Simulation::generate_programme(Cinema& cinema, Logger& logger)
{
    // Generowanie losowego dnia tygodnia
    Day day = generate_random_day();

    // Tworzenie wektora na seanse dla danego dnia
    std::vector<Showing> showings;
    std::chrono::system_clock::time_point base_start_time = std::chrono::system_clock::now() + std::chrono::hours(2); // Bazowy czas rozpoczęcia

    for (int i = 0; i < 3; ++i) { // Tworzymy trzy seanse na dzień
        std::chrono::system_clock::time_point start_time = base_start_time + std::chrono::hours(i * 3); // Dodajemy odstęp 3 godzin między seansami
        Showing showing = generate_random_showing(start_time); // Generujemy losowy seans z różnymi godzinami
        showings.push_back(showing); // Dodajemy seans do wektora
    }

    Programme programme(showings, day); // Tworzymy nowy program dla danego dnia z wygenerowanymi seansami

    cinema.add_programme(programme); // Dodajemy program do kina
}



Film Simulation::generate_random_film()
{
    // Generowanie losowego filmu
    std::vector<std::string> titles = {"The Matrix", "Inception", "Interstellar", "The Dark Knight", "Pulp Fiction", "Fight Club", "The Shawshank Redemption", "Forrest Gump"};
    std::vector<std::string> directors = {"Christopher Nolan", "Quentin Tarantino", "David Fincher", "Martin Scorsese", "Steven Spielberg", "James Cameron"};
    std::vector<int> durations = {120, 150, 180, 135, 160, 200};
    std::vector<int> minimum_ages = {12, 15, 18, 12, 15, 18, 12, 15};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> title_dist(0, titles.size() - 1);
    std::uniform_int_distribution<> director_dist(0, directors.size() - 1);
    std::uniform_int_distribution<> duration_dist(0, durations.size() - 1);
    std::uniform_int_distribution<> age_dist(0, minimum_ages.size() - 1);

    std::string title = titles[title_dist(gen)];
    std::string director = directors[director_dist(gen)];
    std::chrono::minutes duration(durations[duration_dist(gen)]);
    int minimum_age = minimum_ages[age_dist(gen)];

    return Film(title, director, duration, minimum_age);
}

Showing Simulation::generate_random_showing(std::chrono::system_clock::time_point start_time)
{
    // Generowanie losowego filmu
    Film film = generate_random_film();

    std::vector<int> room_numbers = {1, 2, 3};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> room_dist(0, room_numbers.size() - 1);

    int room_number = room_numbers[room_dist(gen)];

    // Losowa liczba rzędów
    unsigned int num_rows = generate_random_number(3, 10); 

    ScreeningRoom room(room_number);

    for (unsigned int i = 0; i < num_rows; ++i) {
        unsigned int num_seats_per_row = generate_random_number(5, 20); 
        room.add_row(Row(i + 1, num_seats_per_row));
    }

    return Showing(film, room, start_time);
}


Day Simulation::generate_random_day()
{
    // Generator liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(Day::Sunday)); // Ustaw zakres od poniedziałku do niedzieli

    // Wylosuj dzień tygodnia
    int random_day_index = dis(gen);
    return static_cast<Day>(random_day_index);
}

int Simulation::generate_random_number(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void Simulation::generate_customers(Cinema& cinema, Logger& logger)
{
    std::vector<std::string> first_names = {"John", "Jane", "Alice", "Bob", "Charlie", "Daisy"};
    std::vector<std::string> last_names = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia"};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> first_name_dist(0, first_names.size() - 1);
    std::uniform_int_distribution<> last_name_dist(0, last_names.size() - 1);
    std::uniform_int_distribution<> age_dist(1, 90);
    std::uniform_int_distribution<> phone_dist(100000000, 999999999);
    std::uniform_int_distribution<> customer_count_dist(1, 10); // Losujemy od 1 do 10 klientów

    int customer_count = customer_count_dist(gen);

    for (int i = 0; i < customer_count; ++i) {
        std::string first_name = first_names[first_name_dist(gen)];
        std::string last_name = last_names[last_name_dist(gen)];
        unsigned int age = age_dist(gen);
        unsigned int phone_number = phone_dist(gen);
        discount my_discount;

        if (age <= 12) {
            my_discount = discount::kid;
        } else if (age >= 13 && age <= 25) {
            my_discount = discount::student;
        } else if (age >= 60) {
            my_discount = discount::senior;
        } else {
            my_discount = discount::no_discount;
        }

        Customer customer(first_name, last_name, age, phone_number, my_discount);
        logger << "Generated customer: " << customer << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));
        cinema.add_customer(customer);
    }
}

void Simulation::generate_duty_rota(Logger& logger)
{
    // Przykład generowania harmonogramu dla różnych pracowników
    std::vector<std::string> doorman_tasks = {"Greet customers", "Check tickets", "Manage entry and exit", "Assist customers with directions", "Ensure safety and security"};
    std::vector<std::string> booking_clerk_tasks = {"Handle reservations", "Check ticket availability", "Assist customers with bookings", "Process ticket sales", "Provide information about screenings"};
    std::vector<std::string> bar_worker_tasks = {"Clean tables", "Prepare drinks", "Serve customers", "Restock inventory", "Cash register duties"};
    std::vector<std::string> manager_tasks = {"Supervise staff", "Handle customer complaints", "Manage inventory", "Coordinate schedules", "Ensure smooth operation of cinema"};

    logger << "Schedule of tasks for the day:" << std::endl;
    logger << "Doorman: " << generate_tasks(doorman_tasks) << std::endl;
    logger << "Booking clerk: " << generate_tasks(booking_clerk_tasks) << std::endl;
    logger << "Bar worker: " << generate_tasks(bar_worker_tasks) << std::endl;
    logger << "Manager: " << generate_tasks(manager_tasks) << std::endl;
    logger << "\n" << std::endl;
}

std::string Simulation::generate_tasks(const std::vector<std::string>& tasks)
{
    std::vector<std::string> daily_tasks;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tasks.size() - 1);

    for (int i = 0; i < 3; ++i) {
        int task_index = dis(gen);
        daily_tasks.push_back(tasks[task_index]);
    }

    std::string result;
    for (const std::string& task : daily_tasks) {
        result += task + ", ";
    }

    return result.substr(0, result.size() - 2); // Usunięcie ostatniego przecinka i spacji
    
}

std::string Simulation::generate_random_name()
{
    std::vector<std::string> names = {"John", "Michael", "Emily", "Sophia", "David"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, names.size() - 1);
    return names[dist(gen)];
}

std::string Simulation::generate_random_surname()
{
    std::vector<std::string> surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, surnames.size() - 1);
    return surnames[dist(gen)];
}

unsigned int Simulation::generate_random_age()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(20, 40); // Random age between 20 and 40
    return dist(gen);
}

Gender Simulation::generate_random_gender()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // Random gender
    return static_cast<Gender>(dist(gen));
}

unsigned int Simulation::generate_random_salary()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1200, 2000); // Random salary between 1200 and 2000
    return dist(gen);
}

Manager Simulation::generate_manager(Cinema& cinema, Logger& logger)
{
    std::vector<std::string> duties = {"Supervise staff", "Handle customer complaints", "Manage inventory", "Coordinate schedules", "Ensure smooth operation of cinema"};
    std::string job_title = "Manager";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> salary_dist(2000, 4000); // Random salary between 2000 and 4000
    unsigned int salary = salary_dist(gen);

    std::uniform_int_distribution<> name_dist(0, 4); // Random name from 5 options
    std::vector<std::string> names = {"John", "Michael", "Emily", "Sophia", "David"};
    std::string name = names[name_dist(gen)];

    std::uniform_int_distribution<> surname_dist(0, 4); // Random name from 5 options
    std::vector<std::string> surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown"};
    std::string surname = surnames[name_dist(gen)];

    std::uniform_int_distribution<> age_dist(25, 55); // Random age between 25 and 55
    unsigned int age = age_dist(gen);

    std::uniform_int_distribution<> gender_dist(0, 1); // Random gender
    Gender gender = static_cast<Gender>(gender_dist(gen));

    Manager manager(name, surname, age, gender, salary, duties, job_title);
    logger << "Today's manager: " << manager << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cinema.add_employee(manager);

    return manager;
}

Doorman Simulation::generate_doorman(Cinema& cinema, Logger& logger)
{
    std::vector<std::string> duties = {"Greet customers", "Check tickets", "Manage entry and exit", "Assist customers with directions", "Ensure safety and security"};
    std::string job_title = "Doorman";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> salary_dist(1200, 1800); // Random salary between 1200 and 1800
    unsigned int salary = salary_dist(gen);

    std::uniform_int_distribution<> name_dist(0, 4); // Random name from 5 options
    std::vector<std::string> names = {"John", "Michael", "Emily", "Sophia", "David"};
    std::string name = names[name_dist(gen)];
    
    std::uniform_int_distribution<> surname_dist(0, 4); // Random name from 5 options
    std::vector<std::string> surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown"};
    std::string surname = surnames[name_dist(gen)];

    std::uniform_int_distribution<> age_dist(20, 40); // Random age between 20 and 40
    unsigned int age = age_dist(gen);

    std::uniform_int_distribution<> gender_dist(0, 1); // Random gender
    Gender gender = static_cast<Gender>(gender_dist(gen));

    Doorman doorman(name, surname, age, gender, salary, duties, job_title);
    logger << "Today's doorman: " << doorman << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cinema.add_employee(doorman);

    return doorman;
}

std::vector<BookingClerk> Simulation::generate_booking_clerks(int count, Cinema& cinema, Logger& logger)
{
    std::vector<BookingClerk> clerks;
    std::vector<std::string> duties = {"Handle reservations", "Check ticket availability", "Assist customers with bookings", "Process ticket sales", "Provide information about screenings"};
    std::string job_title = "Booking Clerk";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> salary_dist(1400, 2000); // Random salary between 1400 and 2000

    for (int i = 0; i < count; ++i) {
        unsigned int salary = salary_dist(gen);

        std::uniform_int_distribution<> name_dist(0, 4); // Random name from 5 options
        std::vector<std::string> names = {"John", "Michael", "Emily", "Sophia", "David"};
        std::string name = names[name_dist(gen)];

        std::uniform_int_distribution<> surname_dist(0, 4); // Random name from 5 options
        std::vector<std::string> surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown"};
        std::string surname = surnames[name_dist(gen)];

        std::uniform_int_distribution<> age_dist(20, 40); // Random age between 20 and 40
        unsigned int age = age_dist(gen);

        std::uniform_int_distribution<> gender_dist(0, 1); // Random gender
        Gender gender = static_cast<Gender>(gender_dist(gen));

        clerks.push_back(BookingClerk(name, surname, age, gender, salary, duties, job_title));
    }

    for (auto& clerk : clerks) {
        logger << "Today's booking clerk: " << clerk << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        generate_counters(cinema, logger, clerk);
        cinema.add_employee(clerk);
    }

    return clerks;
}


std::vector<BarWorker> Simulation::generate_bar_workers(int count, Cinema& cinema, Logger& logger)
{
    std::vector<BarWorker> workers;
    std::vector<std::string> duties = {"Clean tables", "Prepare drinks", "Serve customers", "Restock inventory", "Cash register duties"};
    std::string job_title = "Bar Worker";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> salary_dist(1200, 1800); // Random salary between 1200 and 1800

    for (int i = 0; i < count; ++i) {
        unsigned int salary = salary_dist(gen);

        std::uniform_int_distribution<> name_dist(0, 4); // Random name from 5 options
        std::vector<std::string> names = {"John", "Michael", "Emily", "Sophia", "David"};
        std::string name = names[name_dist(gen)];

        std::uniform_int_distribution<> surname_dist(0, 4); // Random name from 5 options
        std::vector<std::string> surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown"};
        std::string surname = surnames[name_dist(gen)];

        std::uniform_int_distribution<> age_dist(20, 40); // Random age between 20 and 40
        unsigned int age = age_dist(gen);

        std::uniform_int_distribution<> gender_dist(0, 1); // Random gender
        Gender gender = static_cast<Gender>(gender_dist(gen));

        workers.push_back(BarWorker(name, surname, age, gender, salary, duties, job_title));
    }

        for (auto& worker : workers) {
        logger << "Today's bar worker: " << worker << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cinema.add_employee(worker);
    }

    return workers;
}


void Simulation::generate_counters(Cinema& cinema, Logger& logger, BookingClerk& clerk) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> counter_number_dist(1, 10); // Random counter number between 1 and 10

    
    unsigned int counter_number = counter_number_dist(gen);

    Counter counter(counter_number);
    logger << "Counter numbered: " << counter.get_counter_number() << " is opened for an employee: " << clerk.get_name() <<
    " " << clerk.get_surname() << "\n" << std::endl;
    cinema.add_counter(counter);
    
}


void Simulation::assign_customers_to_showings_and_choose_row(Cinema& cinema, Logger& logger) {
    std::random_device rd;
    std::mt19937 gen(rd());
    

    while (!cinema.get_customers().empty()) {
        Customer customer = cinema.get_customers().front();
        logger << "\nCustomer:" << customer.get_name() << " " << customer.get_surname() <<
        " approached to counter number: " << cinema.get_random_counter() << "\n";
        logger << "**CUSTOMER SERVICE ONGOING**" << std::endl;

        cinema.get_customers().pop(); // Remove the customer from the queue

        std::uniform_int_distribution<> programme_dist(0, cinema.get_programmes().size() - 1);
        int programme_index = programme_dist(gen);
        Programme& programme1 = cinema.get_programme(programme_index);
        auto showings = programme1.get_showing(); // przypisanie seansów z danego repertuaru

        std::uniform_int_distribution<> showing_dist(0, showings.size() - 1);
        int showing_index = showing_dist(gen);
        Showing& showing = showings[showing_index];
        logger << " " << std::endl;
        logger << "Customer: " << customer.get_name() << " " << customer.get_surname() << " aged " << customer.get_age() <<
        " years old, has choosen: \n" << showing.get_film().get_title() << ", which minimum age is: " <<
        showing.get_film().get_minimum_age() << std::endl;
        
        if(showing.get_film().get_minimum_age() > customer.get_age()){
            logger << "\nDear, " << customer.get_name() << " " << customer.get_surname() << " ! Sorry, but you are too young to watch -" << showing.get_film().get_title() << 
            ". Cinema cannot generate you a ticket :(\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else{
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> row_dist(0, showing.get_screening_room().get_rows().size() - 1);
            int row_index = row_dist(gen);
            Row& row = showing.get_screening_room().get_row(row_index);
            if(row.get_seats_count() > 0){
                logger << "\nCustomer " << customer.get_name() << " " << customer.get_surname()
                    << " has choosen: " << row.get_row_number() << " row.\n" << std::endl;
                showing.get_screening_room().get_row(row_index).assign_seat();
                
            }
            else{
                logger << "\nNo seat available in row: " << row.get_row_number() << "\n" << std::endl;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> row_dist(0, showing.get_screening_room().get_rows().size() - 1);
                int row_index = row_dist(gen);
                Row row = showing.get_screening_room().get_row(row_index);
                logger << "\nCustomer " << customer.get_name() << " " << customer.get_surname()
                    << " has choosen: " << row.get_row_number() << " row.\n" << std::endl;
                showing.get_screening_room().get_row(row_index).assign_seat();
            }
            generate_ticket(cinema, customer, showing, row, logger);
        }
    }
}

void Simulation::generate_ticket(Cinema& cinema, Customer& customer, Showing& showing, Row row, Logger& logger){
    Ticket ticket;
     switch (customer.get_discount()) {
            case discount::no_discount:
                ticket.set_price(25.0f);
                break;
            case discount::kid:
                ticket.set_price(17.0f);
                break;
            case discount::student:
                ticket.set_price(20.0f);
                break;
            case discount::senior:
                ticket.set_price(20.0f);
                break;
        }
    ticket.set_showing_title(showing.get_film().get_title());
    ticket.set_showing_date(showing.get_start_time());
    ticket.set_row_number(row.get_row_number());
    ticket.show_data(ticket, logger);
}
