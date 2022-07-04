#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>
#include <string>

using namespace std::chrono;

class Timer
{
private:
    time_point<steady_clock,duration<long long int, std::ratio<1, 1000000000>>> startTime;
    time_point<steady_clock,duration<long long int, std::ratio<1, 1000000000>>> endTime;

public:
    void start();
    void stop();
    void displayChrono();
    std::string currentTime();
};

#endif // TIMER_H
