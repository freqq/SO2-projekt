//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_WAITFORINPUT_HPP
#define SO2_FILOZOFOWIE_WAITFORINPUT_HPP

#include <thread>
#include <iostream>
#include <vector>
#include "Philosopher.hpp"

class WaitForInput {
private:
    std::vector<Philosopher*>* philosophers;

    void wait();

public:
    WaitForInput(std::vector<Philosopher*>* philosophers);

    std::thread spawnThread();
};


#endif //SO2_FILOZOFOWIE_WAITFORINPUT_HPP
