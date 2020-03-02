//
// Created by Przemysław Wit on 2020-03-02.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP

#include "Fork.hpp"

enum State {
    EATING,
    THINKING
};

class Philosopher {
private:
    Fork* _left_fork;
    Fork* _right_fork;
    std::string _name;
    State _state;
    int _progress;

    void pick_up_forks();
    void put_down_forks();

public:
    Philosopher(Fork* left_fork, Fork* right_fork);
    Philosopher(Fork* left_fork, Fork* right_fork, std::string name);

    std::string get_name();
    State get_state();
    int get_progress();
    void eat();
    void think();
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
