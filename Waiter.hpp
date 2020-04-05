//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_WAITER_HPP
#define SO2_FILOZOFOWIE_WAITER_HPP

#include "Philosopher.hpp"
#include <vector>
#include <condition_variable>

enum Waiter_State {
    WAITER_NOT_STARTED,
    WAITER_SLEEPING,
    WAITER_CHECKING_QUEUE,
    WAITER_DEAD
};

class Waiter {
private:
    std::mutex forksQueueMutex;
    std::mutex stateMutex;
    std::mutex waiterMutex;

    std::vector<bool> forks; // FALSE - used, TRUE - free
    std::vector<Philosopher*> queue;

    Waiter_State state;
    std::condition_variable waiterSleep;

    bool terminate;
    int numberOfPhilosophers;
    bool checkQueue;

    void setState(Waiter_State state);

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
