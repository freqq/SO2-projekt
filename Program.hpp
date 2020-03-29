//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PROGRAM_HPP
#define SO2_FILOZOFOWIE_PROGRAM_HPP

#include "Philosopher.hpp"
#include <thread>
#include <iostream>
#include <vector>

class Program {
private:
    static int numberOfPhilosophers;
    static std::vector<Philosopher> philosophers;
    static std::vector<std::thread> threads;
    static time_t startTime;

    static void showHeader();
    static bool showThreadsStatus();

public:
    static void start();
};


#endif //SO2_FILOZOFOWIE_PROGRAM_HPP
