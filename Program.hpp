//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PROGRAM_HPP
#define SO2_FILOZOFOWIE_PROGRAM_HPP

#define numberOfPhilosophers 5

#include <thread>
#include <iostream>
#include "Philosopher.hpp"

class Program {
private:
    static Philosopher* philosophers[numberOfPhilosophers];
    static std::thread threads[numberOfPhilosophers];
    static time_t startTime;

public:
    static void start();
    static bool showPhilosophersStatus();
};


#endif //SO2_FILOZOFOWIE_PROGRAM_HPP
