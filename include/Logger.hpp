#pragma once


#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <thread>

//this doesn't need to be done, I was just trying to use templates
//This could be done easily with inheritance anyway

template <typename OutputMethod>
class Logger : private OutputMethod {
public:

    void startTimer() {
        _start = std::chrono::high_resolution_clock::now();
    }

    void endTimer() {
        _stop = std::chrono::high_resolution_clock::now();
        _duration = std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start);

        std::ostringstream oss;
        oss << "\nTime taken:  " << _duration.count() << " milliseconds" << std::endl;
        OutputMethod::output(oss.str());
    }

    void sleep(size_t seconds)
    {
        std::chrono::seconds sleepDuration(seconds);
        std::this_thread::sleep_for(sleepDuration);

    }

    void log(const std::string& message)
    {
            OutputMethod::output(message);
    }


private:
    std::chrono::milliseconds _duration;
    std::chrono::steady_clock::time_point _start, _stop;

};


class ConsoleOutput {
public:
    static void output(const std::string& message) {
        std::cout << message << std::endl;
    }
};

class FileOutput {
public:
    FileOutput() {
        if (std::filesystem::exists("log.txt"))
            std::filesystem::remove("log.txt");
    }
    ~FileOutput() {
        _outfile.close();
    }

    void output(const std::string& message) {
        _outfile = std::ofstream("log.txt", std::ofstream::app);
        _outfile << message << std::endl;

    }
private:
    std::ofstream _outfile;

};