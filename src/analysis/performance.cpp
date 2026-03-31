#include <iostream>
#include "performance.h"
using namespace std;

void Performance::log(string operation, int steps) {
    cout << "\n[PERFORMANCE LOG]\n";
    cout << "Operation: " << operation << endl;
    cout << "Steps: " << steps << endl;
    cout << "----------------------\n";
}