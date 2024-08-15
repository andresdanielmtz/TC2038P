#include <iostream>
#include <list>
#include <string>
#include <vector>

class HashTable {
private:
  std::vector<std::list<std::pair<int, std::string>>> table;
  int size;
  int numElements;

  int hashFunction(int key) const { return key % size; }

  void resize(int new_size) {
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

public:
  HashTable(int s) : size(s), numElements(0) { table.resize(size); }

  double getLoadFactor() const {
    return static_cast<double>(numElements) / size;
  }

  void insert(int key, const std::string &value) {
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

    chain.push_back(std::make_pair(key, value));
    ++numElements;
  }

  std::string search(int key) const {
    int hashIndex = hashFunction(key);
    const auto &chain = table[hashIndex];

    for (const auto &pair : chain) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    return "Key not found";
  }

  void remove(int key) {
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

  void displayTable() const {
    for (int i = 0; i < size; i++) {
      std::cout << "Index " << i << ": ";
      for (const auto &pair : table[i]) {
        std::cout << "(" << pair.first << ", " << pair.second << ") -> ";
      }
      std::cout << "NULL" << std::endl;
    }
  }
};

int main() {
  HashTable ht(10);

  ht.insert(1, "Value1");
  ht.insert(2, "Value2");
  ht.insert(12, "Value3");
  ht.insert(22, "Value4");

  ht.displayTable();

  ht.insert(3, "Value5");
  ht.insert(4, "Value6");
  ht.insert(5, "Value7");
  ht.insert(6, "Value8");
  ht.insert(7, "ValueIncreible");
  ht.insert(8, "ValueAwesome");
  ht.insert(9, "Value9");

  std::cout << "Load Factor: " << ht.getLoadFactor() << std::endl;

  ht.displayTable();

  return 0;
}
