#ifndef HASHVECTOR_H
#define HASHVECTOR_H

#include <iostream>
#include <vector>

class HashVector {
private:
    std::vector<std::pair<int, std::vector<int>>> table;
    int size;
    int numElements;

    int hashFunction(int key) const;
    void resize(int new_size);

public:
    HashVector(int s);
    ~HashVector();  // Destructor to clean up dynamically allocated memory
    double getLoadFactor() const;
    void insert(int key, const std::vector<int>& values);
    std::vector<int> search(int key) const;
    void remove(int key);
    void displayTable() const;
    int getHashTableSize() const;
    void modify(int key, const std::vector<int>& values);
};

#endif // HASHVECTOR_H