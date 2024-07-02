#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

class Logger {
private:
    std::ofstream fileStream;

public:
    Logger(const std::string& filename) : fileStream(filename, std::ios::out | std::ios::app) {
        if (!fileStream.is_open()) {
            throw std::runtime_error("Cannot open file");
        }
    }//otwiera plik tekstowy do zapisu lub wyrzuca wyjątek

    template <typename T>
    Logger& operator<<(const T& data) {
        std::cout << data;
        if (fileStream.is_open()) {
            fileStream << data;
        }
        return *this;
    }

    Logger& operator<<(std::ostream& (*manip)(std::ostream&)) {
        manip(std::cout);
        if (fileStream.is_open()) {
            manip(fileStream);
        }
        return *this;
    }//Zapewnia, że manipulatory mogą być używane zarówno z std::cout, jak i fileStream
};

#endif