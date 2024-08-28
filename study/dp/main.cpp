#include "HashTable.h"
#include <iostream>
// Complexity:
// Time: O(n)
// Because we are calculating the Fibonacci number for each index from 0 to n.
// But for each index, we are only calculating it once. So the time complexity
// is O(n).
unsigned long long fib(int n, HashTable &memo) {
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
  unsigned long long result = fib(n - 1, memo) + fib(n - 2, memo);
  memo.insert(n, result);
  return result;
}
/**
 * @brief Calculates the Fibonacci number for a given index using memoization.
 *
 * @param n The index of the Fibonacci number to calculate.
 * @param memo The hash table used for memoization.
 * @return The Fibonacci number at the given index.
 */

int main() {
  HashTable memo(10);
  int n = 10;
  for (int i = 0; i < 120; i++) {
    std::cout << "Fibonacci(" << i << ") = " << fib(i, memo) << std::endl;
  }
  return 0;
}
