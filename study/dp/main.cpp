#include "HashTable.h"
#include <iostream>

long fib(int n, HashTable &memo) {
  int val = memo.search(n);
  if (val != -1) {
    return val;
  }
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  long result = fib(n - 1, memo) + fib(n - 2, memo);
  memo.insert(n, result);
  return result;
}
int main() {
  HashTable memo(10);
  int n = 10;
  for (int i = 0; i < 100; i++) {
    std::cout << "Fibonacci(" << i << ") = " << fib(i, memo) << std::endl;
  }
  return 0;
}
