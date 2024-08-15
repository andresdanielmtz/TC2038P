#include "HashTable.h"

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
  ht.insert(7, "Value12");

  std::cout << "Load Factor: " << ht.getLoadFactor() << std::endl;

  ht.displayTable();

  return 0;
}
