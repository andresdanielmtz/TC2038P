#ifndef HASHTABLE_H
#define HASHTABLE_H

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
};

#endif // HASHTABLE_H