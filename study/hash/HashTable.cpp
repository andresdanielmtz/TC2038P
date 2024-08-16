#include "HashTable.h"

HashTable::HashTable(int s) : size(s), numElements(0) { table.resize(size); }

int HashTable::hashFunction(int key) const { return key % size; }

void HashTable::resize(int new_size) {
  std::vector<std::list<std::pair<int, std::string>>> new_table(new_size);

  for (int i = 0; i < size; i++) {
    for (auto &pair : table[i]) {
      int new_hash_index = pair.first % new_size;
      new_table[new_hash_index].push_back(pair);
    }
  }

  table = std::move(new_table);
  size = new_size;
}

double HashTable::getLoadFactor() const {
  return static_cast<double>(numElements) / size;
}
void HashTable::insert(int key, const std::string &value) {
  if (getLoadFactor() >= 0.8) {
    resize(size * 2);
  }

  int hashIndex = hashFunction(key);
  auto &chain = table[hashIndex];

  for (auto &pair : chain) {
    if (pair.first == key) {
      pair.second = value;
      return;
    }
  }

  // Probing
  int probeIndex = (hashIndex + 1) % size;
  while (probeIndex != hashIndex) {
    auto &probeChain = table[probeIndex];
    if (probeChain.empty()) {
      probeChain.push_back(std::make_pair(key, value));
      ++numElements;
      return;
    }
    probeIndex = (probeIndex + 1) % size;
  }

  resize(size * 2);
  insert(key, value);
}

std::string HashTable::search(int key) const {
  int hashIndex = hashFunction(key);
  const auto &chain = table[hashIndex];

  for (const auto &pair : chain) {
    if (pair.first == key) {
      return pair.second;
    }
  }
  return "Key not found";
}

void HashTable::remove(int key) {
  int hashIndex = hashFunction(key);
  auto &chain = table[hashIndex];

  for (auto it = chain.begin(); it != chain.end(); ++it) {
    if (it->first == key) {
      chain.erase(it);
      --numElements;
      return;
    }
  }
}

void HashTable::displayTable() const {
  for (int i = 0; i < size; i++) {
    std::cout << "Index " << i << ": ";
    for (const auto &pair : table[i]) {
      std::cout << "(" << pair.first << ", " << pair.second << ") -> ";
    }
    std::cout << "NULL" << std::endl;
  }
}
