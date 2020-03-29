//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_WAITER_HPP
#define SO2_FILOZOFOWIE_WAITER_HPP

#include <vector>
#include <condition_variable>
#include "Philosopher.hpp"

class Waiter {
private:
    std::vector<bool> forks; // FALSE - used, TRUE - free
    std::vector<Philosopher*> queue;

    std::condition_variable waiterSleep;
    std::mutex waiterMutex;

    bool terminate;
    int numberOfPhilosophers;

public:
    Waiter(int numberOfPhilosophers);
    void start();
    void askForForks(Philosopher* philosopher);
    void returnForks(Philosopher* philosopher);
    void setTerminate(bool terminate);
};


#endif //SO2_FILOZOFOWIE_WAITER_HPP
