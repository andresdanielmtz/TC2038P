#include "HashTable.h"
#include <iostream>

void setUpHashTable(HashTable &table) {
  table.insert(500, 0);
  table.insert(200, 0);
  table.insert(100, 0);
  table.insert(50, 0);
  table.insert(20, 0);
  table.insert(10, 0);
  table.insert(5, 0);
  table.insert(2, 0);
  table.insert(1, 0);
}

void dynamic(int p, int q) {
  HashTable h(10); // Arbitrary Val
  setUpHashTable(h);
  h.displayTable();
  int change = p - q;
    for 

}
int main() {
  int p = 10;
  int q = 13;
  dynamic(p, q);
}