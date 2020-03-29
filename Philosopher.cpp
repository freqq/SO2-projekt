//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Philosopher.hpp"
#include "Program.hpp"
#include <random>
#include <chrono>

void Philosopher::setState(unsigned char state) {
    stateMutex->lock();
    Philosopher::state = state;
    stateMutex->unlock();
}

void Philosopher::think(unsigned int seconds) {
    setState(1);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Philosopher::eat() {
    setState(2);
    waiter -> askForForks(this);
    philosopherSleep -> wait(*uniqueLock, [this]{return forksAvailable;});
    setState(3);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    waiter -> returnForks(this);
}

Philosopher::Philosopher(unsigned int id, Waiter* waiter) {
    this -> id = id;
    this -> waiter = waiter;
    forksAvailable = false;
    stateMutex = new std::mutex;
    setState(0);
}

void Philosopher::live() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1,10);

    uniqueLock = new std::unique_lock<std::mutex>(*philosopherMutex);

    for(int i = 0; i < 5; i++){
        think((unsigned int) distribution(mt));
        eat();
    }

    setState(4);
}

std::thread Philosopher::spawnThread() {
    return std::thread([this] {this -> live();});
}

unsigned char Philosopher::getState() const {
    std::unique_lock<std::mutex> uniqueLock(*stateMutex);
    return state;
}

unsigned int Philosopher::getId() const {
    return id;
}

void Philosopher::wakeUp() {
    forksAvailable = true;
    philosopherSleep -> notify_all();
}

