//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Philosopher.hpp"
#include <random>
#include <unistd.h>

void Philosopher::think(unsigned int seconds) {
    state = false;
    sleep(seconds);
}

void Philosopher::eat() {
    state = true;
    sleep(2);
}

Philosopher::Philosopher(unsigned int id) {
    this->id = id;
    leftFork = true;
    rightFork = true;
}

void Philosopher::live() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1,10);

    for(int i = 0; i < 5; i++){
        think((unsigned int) distribution(mt));
        eat();
    }
}