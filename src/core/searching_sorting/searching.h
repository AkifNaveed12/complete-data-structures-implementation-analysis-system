#ifndef SEARCHING_H
#define SEARCHING_H

#include "../../analysis/visual.h"
#include "../../analysis/performance.h"
#include <string>

class Searching {
public:
    static int linearSearch(int arr[], int n, int key);
    static int binarySearch(int arr[], int n, int key);
};

#endif
