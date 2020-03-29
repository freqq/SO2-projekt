//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PROGRAM_HPP
#define SO2_FILOZOFOWIE_PROGRAM_HPP

#include <thread>
#include <iostream>
#include "Philosopher.hpp"

class Program {
private:
    static Philosopher* philosophers[5];
    static std::thread threads[5];
    static time_t startTime;

public:
    static void start();
    static void showPhilosophersStatus();
};


#endif //SO2_FILOZOFOWIE_PROGRAM_HPP
