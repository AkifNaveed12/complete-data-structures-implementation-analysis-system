#ifndef VISUAL_H
#define VISUAL_H

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

inline void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif