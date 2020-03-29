//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP

#include <iostream>
#include <thread>
#include <mutex>

class Philosopher {
private:
    unsigned int id;

    bool leftFork; // false if used, true if free
    bool rightFork;

    std::mutex * stateMutex;
    unsigned char state; // 0 - not started yet, 1 - thinking, 2 - sleeping(waiting for forks), 3 - eating, 4 - dead

    void setState(unsigned char state);
    void think(unsigned int seconds);
    void eat();
    void live();

public:
    Philosopher(unsigned int id);
    std::thread spawnThread();
    unsigned char getState() const;
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
