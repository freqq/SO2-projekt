//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Philosopher.hpp"
#include "Program.hpp"
#include <random>
#include <chrono>

void Philosopher::setState(Philosopher_State state) {
    stateMutex.lock();
        Philosopher::state = state;
    stateMutex.unlock();
}

void Philosopher::think(unsigned int deciSeconds) {
    setState(Philosopher_State::THINKING);
    std::this_thread::sleep_for(std::chrono::milliseconds(deciSeconds * 100));
}

void Philosopher::eat() {
    forksAvailabilityMutex.lock();
        setState(Philosopher_State::SLEEPING);
        waiter -> askForForks(this);
    forksAvailabilityMutex.unlock();

    philosopherSleep.wait(uniqueLock, [this]{return forksAvailable;});

    forksAvailabilityMutex.lock();
        setState(Philosopher_State::EATING);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        forksAvailable = false;
        waiter -> returnForks(this);
    forksAvailabilityMutex.unlock();
}

Philosopher::Philosopher(unsigned int id, Waiter* waiter) {
    this -> id = id;
    this -> waiter = waiter;
    forksAvailable = false;
    terminate = false;
    this -> state = Philosopher_State::NOT_STARTED;
}

void Philosopher::live() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1,100);

    uniqueLock = std::unique_lock<std::mutex>(philosopherMutex);

    while(!terminate){
        think((unsigned int) distribution(mt));
        eat();
    }

    setState(Philosopher_State::DEAD);
}

std::thread Philosopher::spawnThread() {
    return std::thread([this] {this -> live();});
}

unsigned char Philosopher::getState() {
    stateMutex.lock();
        unsigned char temp = state;
    stateMutex.unlock();

    return temp;
}

unsigned int Philosopher::getId() {
    return id;
}

void Philosopher::wakeUp() {
    forksAvailabilityMutex.lock();
        forksAvailable = true;
        philosopherSleep.notify_all();
    forksAvailabilityMutex.unlock();
}

void Philosopher::setTerminate(bool terminate) {
    Philosopher::terminate = terminate;
}
