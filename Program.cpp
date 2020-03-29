//
// Created by Przemysław Wit on 2020-03-29.
//

#include "Program.hpp"
#include "WaitForInput.hpp"
#include <chrono>
#include <fstream>
#include <vector>

int Program::numberOfPhilosophers = 5;

Waiter* Program::waiter = new Waiter(Program::numberOfPhilosophers);

std::vector<Philosopher*> Program::philosophers;
std::vector<std::thread> Program::threads;

time_t Program::startTime;

bool Program::fileExport = false;
bool Program::shouldTerminate = false;

void Program::start() {
    std::cout << "Save simulation output to file? [Y/N]: ";
    char tempChar = 'n';
    std::cin >> tempChar;

    if (tempChar == 'Y' || tempChar == 'y')
        fileExport = true;

    std::fstream* file;

    if(fileExport){
        std::string path = std::to_string(time(0));
        path += "-DiningPhilosophersProblem-" + std::to_string(numberOfPhilosophers) + ".txt";

        file = new std::fstream(path, std::fstream::out);

        if (!file->is_open()) {
            std::cout << "There was a problem with creating a file. "
                         "The app will continue without saving the output into a file." << std::endl;
        } else {
            std::cout << "Saving a simulation output to: " << path << std::endl;
        }
    }


    std::thread waiterThread = waiter -> spawnThread();

    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        philosophers.push_back(new Philosopher(i, waiter));
    }

    std::string buffer = "";
    buffer = getHeader();

    std::cout << buffer;
    if(fileExport)
        (*file) << buffer;

    time(&startTime);

    for (auto &philosopher : philosophers)
        threads.emplace_back(philosopher -> spawnThread());

    WaitForInput waitForInput(&philosophers);
    std::thread waitThread = waitForInput.spawnThread();

    while(!shouldTerminate){
        buffer = getThreadsStatus();

        std::cout << buffer;
        if(fileExport)
            (*file) << buffer;

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    waitThread.join();
    waiter -> setTerminate(true);

    for (auto &thread : threads)
        thread.join();

    waiter -> wakeUp();
    waiterThread.join();

    buffer = "Simulation over. \n";

    std::cout << buffer;
    if(fileExport){
        (*file) << buffer;
        file -> close();
    }
}

std::string Program::getThreadsStatus() {
    std::string output = "";

    time_t currentTime;
    time(&currentTime);

    std::string diffTime = std::to_string((int) difftime(currentTime, startTime));

    output += diffTime;
    for (int i = 0; i < (5 - diffTime.length()); i++) {
        output += " ";
    }
    output += "| ";

    bool shouldTerminate = false;
    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        if (i == 0){
            if (philosophers[i] -> getState() == Philosopher_State::DEAD)
                shouldTerminate = true;
            else
                shouldTerminate = false;
        } else {
            if(shouldTerminate && philosophers[i] -> getState() == Philosopher_State::DEAD)
                shouldTerminate = true;
            else
                shouldTerminate = false;
        }

        if (philosophers[i] -> getState() == Philosopher_State::DEAD) {
            output += "Dead";
            output += "         ";
        } else if (philosophers[i] -> getState() == Philosopher_State::EATING) {
            output += "Eating";
            output += "       ";
        } else if (philosophers[i] -> getState() == Philosopher_State::SLEEPING) {
            output += "Waiting";
            output += "      ";
        } else if (philosophers[i] -> getState() == Philosopher_State::THINKING) {
            output += "Thinking";
            output += "     ";
        } else if (philosophers[i] -> getState() == Philosopher_State::NOT_STARTED) {
            output += "Not started yet";
        } else {
            output += "Error!";
            output += "       ";
        }

        output += " | ";
    }

    if (waiter -> getState() == Waiter_State::WAITER_DEAD) {
        output += "Dead";
        output += "         ";
    } else if (waiter -> getState() == Waiter_State::WAITER_CHECKING_QUEUE) {
        output += "Checking";
        output += "     ";
    } else if (waiter -> getState() == Waiter_State::WAITER_SLEEPING) {
        output += "Sleeping";
        output += "     ";
    } else if (waiter -> getState() == Waiter_State::WAITER_NOT_STARTED)
        output += "Not yet start";
    else {
        output += "Error!";
        output += "       ";
    }

    output += " | ";
    std::vector<bool> forks = waiter->getForks();

    for(int i = 0; i < forks.size(); i++) {
        if (forks[i]) {
            output += "Free";
            output += "    ";
        } else if (!forks[i]) {
            output += "Occupied";
            output += "";
        } else {
            output += "Error!";
            output += "  ";
        }
        if (i < numberOfPhilosophers - 1)
            output += " | ";
        else
            output += "\n";
    }

    return output;
}

std::string Program::getHeader() {
    std::string output = "";

    output += "Time | ";
    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        output += "Philosopher " + std::to_string(i);
        output += " | ";
    }

    std::cout<<"Waiter       "<<" | ";
    for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
        output += "Fork " + std::to_string(i) + "  ";
        if (i < numberOfPhilosophers - 1)
            output += " | ";
        else
            output += "\n";
    }

    for (unsigned int i = 0; i < 155; i++)
        output += "-";

    output += "\n";

    return output;
}