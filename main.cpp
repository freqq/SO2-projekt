#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ncurses.h>
#include <mutex>
#include <unistd.h>
#include "Philosopher.hpp"
#include "Fork.hpp"


std::vector<Philosopher> philosophers;
const int THREADS_NUMBER = 5;

void philisopher_lifecycle(Philosopher* philosopher, std::atomic<bool>& running) {
    while(running) {
        philosopher -> think();
        philosopher -> eat();
    }
}

void display(std::atomic<bool>& displaying) {
    while(displaying) {
        clear();
        for(int i = 0; i < THREADS_NUMBER; i++) {
            mvprintw(i+1, 0, philosophers[i].get_name().c_str());

            switch (philosophers[i].get_state()){
                case State::EATING:
                    mvprintw(i+1, 15, "eating");
                    break;
                case State::THINKING:
                    mvprintw(i+1, 15, "thinking");
                    break;
            }

            mvprintw(i+1, 40, std::to_string(philosophers[i].get_progress()).c_str());
        }

        refresh();

        usleep(10000);
    }
}


int main() {
    srand(time(NULL));

    initscr();
    refresh();

    std::thread threads(THREADS_NUMBER);

    for(int i = 0; i < THREADS_NUMBER; i++){
        std::string name("philosopher");
        philosophers.push_back(new Philosopher(new Fork(), new Fork(), name + std::to_string(i)));
    }

    std::atomic<bool> running(true);

    for(int i = 0; i < THREADS_NUMBER; i++)
        threads[i] = std::thread(philisopher_lifecycle, philosophers[i], std::ref(running));

    std::atomic<bool> displaying(true);

    std::thread displayThread(display, ref(displaying));

    int esc = 0;
    do {
        noecho();
        esc = getch();
    } while (esc != 27);

    running = false;
    displaying = false;

    for(int i = 0; i < THREADS_NUMBER; i++)
        threads[i].join();

    displayThread.join();

    endwin();

    return 0;
}