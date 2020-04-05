//
// Created by Przemysław Wit on 2020-03-29.
//

#include "WaitForInput.hpp"

void WaitForInput::wait() {
    char c = 0;
    while (c != 'q')
        scanf(" %c", &c);

    int i = 0;
    for (auto &philosopher : *philosophers) {
        philosopher -> setTerminate(true);
        std::cout << "Setting PHILOSOPHER " << i << " state = DEAD ... " << std::endl;
        i++;
    }
}

std::thread WaitForInput::spawnThread() {
    return std::thread([this] {this -> wait();});
}

WaitForInput::WaitForInput(std::vector<Philosopher *> *philosophers) {
    this -> philosophers = philosophers;
}