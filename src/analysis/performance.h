#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <string>
#include <vector>

using namespace std;

struct Record {
    string operation;
    int steps;
};

class Performance {
private:
    static vector<Record> logs;

public:
    static void log(string operation, int steps);
    static void display();
};

#endif