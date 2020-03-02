//
// Created by Przemysław Wit on 2020-03-02.
//

#include "Philosopher.hpp"
#include <thread>
#include <cstdlib>
#include <unistd.h>

Philosopher::Philosopher(Fork *left_fork, Fork *right_fork) {
    _left_fork = left_fork;
    _right_fork = right_fork;
}

Philosopher::Philosopher(Fork *left_fork, Fork *right_fork, std::string name) : Philosopher(left_fork, right_fork) {
    _name = name;
}

void Philosopher::think() {
    _state = State::THINKING;
    _progress = 0;

    for(int i=0; i < 10; i++){
        _progress++;
        usleep(350000 + std::rand() % 100000);
    }
}

void Philosopher::eat() {
    pick_up_forks();

    _state = State::EATING;
    _progress = 0;

    for(int i = 0; i < 10; i++){
        _progress++;
        usleep(350000 + std::rand() % 100000);
    }

    put_down_forks();
}

void Philosopher::put_down_forks() {
    _left_fork->put_down();
    _right_fork->put_down();
}

void Philosopher::pick_up_forks() {
    _left_fork->take();
    _right_fork->take();
}

std::string Philosopher::get_name() {
    return _name;
}

State Philosopher::get_state() {
    return _state;
}

int Philosopher::get_progress() {
    return _progress;
}

