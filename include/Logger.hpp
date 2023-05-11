#pragma once


#include <iostream>
#include <chrono>

class Logger {
public:

    void startTimer() {
        _start = std::chrono::high_resolution_clock::now();
    }

    void endTimer() {
        _stop = _start = std::chrono::high_resolution_clock::now();
        _duration = std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start);
        std::cout << "\nTime taken: " << _duration.count() << " milliseconds" << std::endl;
    }

private:
    std::chrono::milliseconds _duration;
    std::chrono::steady_clock::time_point _start, _stop;

};