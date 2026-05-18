#ifndef HASH_H
#define HASH_H

#include "../../analysis/visual.h"
#include "../../analysis/performance.h"
#include <string>

#define TABLE_SIZE 10

struct HashNode {
    int key;
    HashNode* next;
    HashNode(int k) : key(k), next(nullptr) {}
};

class HashChaining {
private:
    HashNode* table[TABLE_SIZE];
    int hashFunction(int key);
public:
    HashChaining();
    void insert(int key);
    void display();
};

class HashLinearProbe {
private:
    int table[TABLE_SIZE];
    int hashFunction(int key);
public:
    HashLinearProbe();
    void insert(int key);
    void display();
};

#endif
