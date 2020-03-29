//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_WAITER_HPP
#define SO2_FILOZOFOWIE_WAITER_HPP

#include "Philosopher.hpp"
#include <vector>
#include <condition_variable>

class Waiter {
private:
    std::mutex forksQueueMutex;
    std::vector<bool> forks; // FALSE - used, TRUE - free
    std::vector<Philosopher*> queue;

    std::mutex stateMutex;
    unsigned char state; // 0 - not started yet; 1 - sleeping; 2 - checking queue; 3 - dead
    std::condition_variable waiterSleep;
    std::mutex waiterMutex;

    bool terminate;
    int numberOfPhilosophers;
    bool checkQueue;
    void setState(unsigned char state);

public:
    Waiter(int numberOfPhilosophers);

    void start();
    void askForForks(Philosopher* philosopher);
    void returnForks(Philosopher* philosopher);
    void setTerminate(bool terminate);
    void wakeUp();

    std::thread spawnThread();
    unsigned char getState();
    const std::vector<bool> getForks();
};


#endif //SO2_FILOZOFOWIE_WAITER_HPP
