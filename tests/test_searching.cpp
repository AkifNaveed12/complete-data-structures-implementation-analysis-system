#include "../src/core/searching_sorting/searching.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Testing Searching Module ===\n";
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    Searching::linearSearch(arr, n, 50);
    Searching::linearSearch(arr, n, 99);
    
    Searching::binarySearch(arr, n, 30);
    Searching::binarySearch(arr, n, 100);
    
    Performance::display();
    return 0;
}
