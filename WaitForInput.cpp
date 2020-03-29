//
// Created by Przemysław Wit on 2020-03-29.
//

#include "WaitForInput.hpp"

void WaitForInput::wait() {
    char c = 0;
    while (c!= 'q') {
        scanf(" %c", &c);
    }

    for (int i = 0; i < philosophers->size(); i++){
        Philosopher* philosopher = (*philosophers)[i];
        philosopher -> setTerminate(true);
    }
}

std::thread WaitForInput::spawnThread() {
    return std::thread([this] {this -> wait();});
}

WaitForInput::WaitForInput(std::vector<Philosopher *> *philosophers) {
    this -> philosophers = philosophers;
}