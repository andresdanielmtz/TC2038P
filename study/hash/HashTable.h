#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

class HashTable {
private:
  std::vector<std::list<std::pair<int, std::string>>> table;
  int size;
  int numElements;

  int hashFunction(int key) const;
  void resize(int new_size);

public:
  HashTable(int s);

  double getLoadFactor() const;
  void insert(int key, const std::string &value);
  std::string search(int key) const;
  void remove(int key);
  void displayTable() const;
};

#endif // HASHTABLE_H
