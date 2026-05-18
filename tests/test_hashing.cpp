#include "../src/core/hashing/hash.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Testing Hashing Module ===\n";
    
    HashChaining hc;
    hc.insert(10);
    hc.insert(20); // collision with 10 if size is 10
    hc.insert(15);
    hc.insert(25); // collision with 15
    
    HashLinearProbe hp;
    hp.insert(10);
    hp.insert(20); // collision -> probes to 11
    hp.insert(15);
    hp.insert(25); // collision -> probes to 16
    
    Performance::display();
    return 0;
}
