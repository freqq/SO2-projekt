//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Waiter.hpp"

Waiter::Waiter(int numberOfPhilosophers) {
    this->numberOfPhilosophers = numberOfPhilosophers;

    for(int i = 0; i < numberOfPhilosophers; i++)
        forks.push_back(true);
}

void Waiter::start() {
    std::unique_lock<std::mutex> uniqueLock(waiterMutex);

    while(!terminate && queue.size() > 0){
        waiterSleep.wait(uniqueLock, [this] {return true;});
        for(auto &philosopher : queue){
            int it = philosopher -> getId();
            int left = id;
            int right = id + 1;
            if (right == numberOfPhilosophers)
                right = 0;
            if (forks[left] && forks[right]){
                forks[left] = false;
                forks[right] = false;
                philosopher -> wakeUp();
            }
        }
    }
}

void Waiter::askForForks(Philosopher *philosopher) {
    queue.push_back(philosopher);
    waiterSleep.notify_all();
}

void Waiter::returnForks(Philosopher *philosopher) {
    int id = philosopher -> getId();
    int left = id;
    int right = id + 1;
    if (right == numberOfPhilosophers)
        right = 0;
    forks[left] = true;
    forks[right] = true;
    waiterSleep.notify_all();
}

void Waiter::setTerminate(bool terminate) {
    Waiter::terminate = terminate;
}