//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP

#include <iostream>
#include <thread>

class Philosopher {
private:
    unsigned int id;

    bool leftFork;
    bool rightFork;

    void think(unsigned int seconds);
    void eat();

public:
    bool state;

    Philosopher(unsigned int id);
    void live();
    std::thread spawnThread();
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
