#include "simulation.hpp"
#include "argument_checker.hpp"

int main(int argc, char* argv[])
{
    ArgumentChecker myArgumentChecker(argc, argv);

    try{
        int days_count{std::stoi(argv[1])};
        std::string txt_path{argv[2]};
        std::string cinema_data_file{argv[3]};

        std::vector<Cinema> cinemas;
        Cinema cinema = Cinema::load_from_file(cinema_data_file);
        cinemas.push_back(Cinema(cinema));
        
        Simulation simulation(cinemas, days_count); 

        simulation.run(txt_path);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; 
    }
    return 0;
}

