//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP

#include "Waiter.hpp"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

class Philosopher {
private:
    unsigned int id;

    std::mutex * stateMutex;
    unsigned char state; // 0 - not started yet, 1 - thinking, 2 - sleeping(waiting for forks), 3 - eating, 4 - dead

    bool forksAvailable;
    Waiter* waiter;

    std::mutex* philosopherMutex;
    std::condition_variable* philosopherSleep;
    std::unique_lock<std::mutex>* uniqueLock;

    void setState(unsigned char state);
    void think(unsigned int seconds);
    void eat();
    void live();

public:
    Philosopher(unsigned int id, Waiter* waiter);
    std::thread spawnThread();
    unsigned char getState() const;
    unsigned int getId() const;
    void wakeUp();
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
