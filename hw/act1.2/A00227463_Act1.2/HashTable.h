#pragma once 

#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<std::pair<int, int> > table;
    int size;
    int numElements;

    int hashFunction(int key) const;
    void resize(int new_size);

public:
    HashTable(int s);
    double getLoadFactor() const;
    void insert(int key, int value);
    int search(int key) const;
    void remove(int key);
    void displayTable() const;
    int getHashTableSize(); 
    void modify(int key, int value); 
};
