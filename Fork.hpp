//
// Created by Przemysław Wit on 2020-03-02.
//

#ifndef SO2_FILOZOFOWIE_FORK_HPP
#define SO2_FILOZOFOWIE_FORK_HPP

#include <mutex>


class Fork {
public:
    Fork();
    void take();
    void put_down();

private:
    std::mutex _mutex;
};


#endif //SO2_FILOZOFOWIE_FORK_HPP
