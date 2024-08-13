#include <cmath>
#include <iostream>

/*
Example: Print all positive integer solutions to the equation a3 + b3 = c3 + d3
where a, b, c, and d are integers between 1 and 1000.

*/

void brute_force(int n) {
  int i, j, k, l, left, right;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < n; k++) {
        for (l = 0; l < n; l++) {
          left = pow(i, 3) + pow(j, 3);
          right = pow(k, 3) + pow(l, 3);
          if (left == right) {
            std::cout << "Correct! \t" << i << " " << j << "\n";
          } else {
            std::cout << "Incorrect : (( \n";
          }
        }
      }
    }
  }
}

// There's only one value of D, therefore we can compute it like
// d = sqrt^3 ( a^3 + b^3 - c^3 )
// It will only optimize o(n^4) to o(n^3), but it is still a good optimization
// nonetheless.

void optimized_method(int n) {
  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < n; k++) {
        int d = pow(pow(i, 3) + pow(j, 3) - pow(k, 3), 1 / 3);
        if (pow(i, 3) + pow(j, 3) == pow(k, 3) + pow(d, 3)) {
          std::cout << i << " " << j << " " << k << " " << d << std::endl;
        }
      }
    }
  }
}

void duplicatedWork(int n) { 

}

int main() {
  std::cout << "Hello, World!" << std::endl;
  optimized_method(10);
  return 0;
}