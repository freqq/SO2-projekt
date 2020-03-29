//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Program.hpp"

Philosopher* Program::philosophers[5];
std::thread Program::threads[5];

time_t Program::startTime;

void Program::start() {
    for (unsigned int i = 0; i < 5; i++) {
        Program::philosophers[i] = new Philosopher(i);
    }


    std::cout << "Time | ";
    for (unsigned int i = 0; i < 5; i++) {
        std::cout << "Philosopher " << i;
        if (i < 4)
            std::cout << " | ";
        else
            std::cout << std::endl;
    }
    for (unsigned int i = 0; i < 77; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    time(&startTime);

    for (unsigned int i = 0; i < 5; i++) {
        threads[i] = philosophers[i]->spawnThread();
    }

    for (unsigned int i = 0; i < 5; i++) {
        threads[i].join();
        for (auto &thread : threads) {
            thread.join();
        }
    }
}

void Program::showPhilosophersStatus() {
    time_t currentTime;
    time(&currentTime);

    std::string diffTime = std::to_string((int) difftime(currentTime, startTime));

    std::cout << diffTime;
    for (int i = 0; i < (5 - diffTime.length()); i++) {
        std::cout << " ";
    }
    std::cout << "| ";

    for (unsigned int i = 0; i < 5; i++) {
        if (philosophers[i]->state) {
            std::cout << "Eating";
            std::cout << "        ";
            std::cout << "       ";
        } else {
            std::cout << "Thinking";
            std::cout << "      ";
            std::cout << "     ";
        }
        if (i < 4)
            std::cout << " | ";
        else
            std::cout << std::endl;
    }
}