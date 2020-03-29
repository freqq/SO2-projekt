//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

class Waiter;

enum Philosopher_State {
    NOT_STARTED,
    THINKING,
    SLEEPING,
    EATING,
    DEAD
};

class Philosopher {
private:
    unsigned int id;

    std::mutex stateMutex;
    Philosopher_State state;

    std::mutex forksAvailabilityMutex;
    bool forksAvailable;
    bool terminate;
    Waiter* waiter;

    std::mutex philosopherMutex;
    std::condition_variable philosopherSleep;
    std::unique_lock<std::mutex> uniqueLock;

    void setState(Philosopher_State state);
    void think(unsigned int deciSeconds);
    void eat();
    void live();

public:
    Philosopher(unsigned int id, Waiter* waiter);

    void wakeUp();
    void setTerminate(bool terminate);

    std::thread spawnThread();
    unsigned char getState();
    unsigned int getId();
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
