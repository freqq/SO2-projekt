//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Waiter.hpp"

void Waiter::setState(unsigned char state) {
    stateMutex.lock();
        Waiter::state = state;
    stateMutex.unlock();
}

Waiter::Waiter(int numberOfPhilosophers) {
    terminate = false;
    checkQueue = false;
    this->numberOfPhilosophers = numberOfPhilosophers;

    for(int i = 0; i < numberOfPhilosophers; i++)
        forks.push_back(true);
}

void Waiter::start() {
    std::unique_lock<std::mutex> uniqueLock(waiterMutex);

    setState(1);
    while (!(terminate && queue.size() == 0)) {
        waiterSleep.wait(uniqueLock, [this] {return checkQueue;});
        forksQueueMutex.lock();
        setState(2);
        checkQueue = false;
        int i = 0;
        for (auto &philosopher : queue) {
            int id = philosopher->getId();
            int left = id;
            int right = id + 1;
            if (right == numberOfPhilosophers)
                right = 0;
            if (forks[left] && forks[right]) {
                forks[left] = false;
                forks[right] = false;
                philosopher->wakeUp();
                queue.erase(queue.begin() + i);
                i--;
            }
            i++;
        }
        setState(1);
        forksQueueMutex.unlock();
    }
    setState(3);
}

void Waiter::askForForks(Philosopher *philosopher) {
    forksQueueMutex.lock();
        queue.push_back(philosopher);
        checkQueue = true;
        waiterSleep.notify_all();
    forksQueueMutex.unlock();
}

void Waiter::returnForks(Philosopher *philosopher) {
    int id = philosopher -> getId();
    int left = id;
    int right = id + 1;

    if (right == numberOfPhilosophers)
        right = 0;

    forksQueueMutex.lock();
    forks[left] = true;
    forks[right] = true;

    checkQueue = true;
    waiterSleep.notify_all();
    forksQueueMutex.unlock();
}

void Waiter::setTerminate(bool terminate) {
    Waiter::terminate = terminate;
}

std::thread Waiter::spawnThread() {
    return std::thread([this] { this -> start(); });
}

unsigned char Waiter::getState() {
    stateMutex.lock();
        unsigned char tmpState = state;
    stateMutex.unlock();

    return tmpState;
}

void Waiter::wakeUp() {
    forksQueueMutex.lock();
    checkQueue = true;
    waiterSleep.notify_all();
    forksQueueMutex.unlock();
}

const std::vector<bool> Waiter::getForks() {
    forksQueueMutex.lock();
        std::vector<bool> tempForks;
        tempForks = forks;
    forksQueueMutex.unlock();

    return tempForks;
}