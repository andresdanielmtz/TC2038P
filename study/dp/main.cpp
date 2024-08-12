// Rodcut Implementation
#include <algorithm>
#include <iostream>
#include <vector>

int cutRod(std::vector<int> p, int n) {
  if (n == 0) {
    return 0;
  }
  int q = -1;

  for (int i = 1; i < n; i++) {
    q = std::max(q, p[i] + cutRod(p, n - 1));
  }
  return q;
}
