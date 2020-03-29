//
// Created by Przemysław Wit on 2020-03-29.
//

#ifndef SO2_FILOZOFOWIE_PHILOSOPHER_HPP
#define SO2_FILOZOFOWIE_PHILOSOPHER_HPP


class Philosopher {
private:
    unsigned int id;

    bool leftFork;
    bool rightFork;

    bool state;

    void think(unsigned int seconds);
    void eat();

public:
    Philosopher(unsigned int id);

    void live();
};


#endif //SO2_FILOZOFOWIE_PHILOSOPHER_HPP
