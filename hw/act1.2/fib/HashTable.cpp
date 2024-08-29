#include "HashTable.h"
#include <cmath>

HashTable::HashTable(int s) : size(s), numElements(0) {
    table.resize(size, std::make_pair(-1, -1));
}

int HashTable::hashFunction(int key) const {
    return std::abs(key) % size;
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(numElements) / size;
}

void HashTable::insert(int key, int value) {
    if (getLoadFactor() > 0.7) {
        resize(size * 2);
    }

    int index = hashFunction(key);
    while (table[index].first != -1 && table[index].first != key) {
        index = (index + 1) % size;
    }

    if (table[index].first == -1) {
        numElements++;
    }
    table[index].first = key;
    table[index].second = value;
}

int HashTable::search(int key) const {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (table[index].first == key) {
            return table[index].second;
        }
        index = (index + 1) % size;
    } while (index != startIndex && table[index].first != -1);

    return -1;  // Key not found
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (table[index].first == key) {
            table[index] = std::make_pair(-1, -1);
            numElements--;
            return;
        }
        index = (index + 1) % size;
    } while (index != startIndex && table[index].first != -1);
}

void HashTable::resize(int new_size) {
    std::vector<std::pair<int, int> > old_table = std::move(table);
    table.resize(new_size, std::make_pair(-1, -1));
    size = new_size;
    numElements = 0;

    for (const auto& entry : old_table) {
        if (entry.first != -1) {
            insert(entry.first, entry.second);
        }
    }
}

void HashTable::displayTable() const {
    for (int i = 0; i < size; i++) {
        if (table[i].first != -1) {
            std::cout << "Index " << i << ": Key = " << table[i].first 
                      << ", Value = " << table[i].second << std::endl;
        }
    }
}

int HashTable::getHashTableSize() { 
    return size;
}