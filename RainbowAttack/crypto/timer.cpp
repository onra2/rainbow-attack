#include "timer.h"
#include <iostream>

void Timer::start(){
    this->startTime = std::chrono::steady_clock::now();
    this->endTime = this->startTime;
}

void Timer::stop(){
    this->endTime = std::chrono::steady_clock::now();
}

void Timer::displayChrono(){
    std::cout << "Chrono :" << std::endl
              << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() <<  " milliseconds " << std::endl
              << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " seconds" << std::endl
              << std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count() << " minutes" << std::endl
              << std::chrono::duration_cast<std::chrono::hours>(endTime - startTime).count() << " hours" << std::endl;
}

std::string Timer::currentTime(){
    std::time_t currentTime = std::time(0);
    return std::ctime(&currentTime);
}
