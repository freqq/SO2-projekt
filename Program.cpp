//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Program.hpp"
#include <chrono>
#include <vector>

int Program::numberOfPhilosophers = 5;

std::vector<Philosopher> Program::philosophers;
std::vector<std::thread> Program::threads;

time_t Program::startTime;

void Program::start() {
    Waiter waiter(numberOfPhilosophers);

    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        philosophers.emplace_back(i, &waiter);
    }

    showHeader();
    time(&startTime);

    for (auto &philosopher : philosophers)
        threads.emplace_back(philosopher.spawnThread());

    bool run = true;
    while(run){
        run = showThreadsStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    waiter.setTerminate(true);

    for (auto &thread : threads)
        thread.join();
}

bool Program::showThreadsStatus() {
    time_t currentTime;
    time(&currentTime);

    std::string diffTime = std::to_string((int) difftime(currentTime, startTime));

    std::cout << diffTime;
    for (int i = 0; i < (5 - diffTime.length()); i++) {
        std::cout << " ";
    }
    std::cout << "| ";

    bool shouldTerminate = false;
    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        if (i == 0){
            if (philosophers[i].getState() == 3)
                shouldTerminate = true;
            else
                shouldTerminate = false;
        } else {
            if(shouldTerminate && philosophers[i].getState() == 3)
                shouldTerminate = true;
            else
                shouldTerminate = false;
        }

        if (philosophers[i].getState() == 3) {
            std::cout << "Dead";
            std::cout << "         ";
        } else if (philosophers[i].getState() == 2) {
            std::cout << "Eating";
            std::cout << "       ";
        } else if (philosophers[i].getState() == 1) {
            std::cout<<"Thinking";
            std::cout<<"     ";
        } else if (philosophers[i].getState() == 0) {
            std::cout << "Not started yet";
        } else {
            std::cout<<"Error!";
            std::cout<<"       ";
        }

        if (i < (numberOfPhilosophers - 1))
            std::cout << " | ";
        else
            std::cout << std::endl;
    }

    return !shouldTerminate;
}

void Program::showHeader() {
    std::cout << "Time | ";
    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        std::cout << "Philosopher " <<i;

        if (i < numberOfPhilosophers - 1)
            std::cout <<" | " ;
        else
            std::cout << std::endl;
    }

    for (unsigned int i = 0; i < 84; i++)
        std::cout << "-";

    std::cout << std::endl;
}