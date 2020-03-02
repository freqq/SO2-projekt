//
// Created by Przemysław Wit on 2020-03-02.
//

#include "Fork.hpp"

Fork::Fork() {
    // Constructor
}

void Fork::take() {
    _mutex.lock();
}

void Fork::put_down() {
    _mutex.unlock();
}