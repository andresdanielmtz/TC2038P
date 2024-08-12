#include <iostream>
#include <vector>

void merge(std::vector<double> &arr, int p, int r, int q) {
  int i, j, k;
  int n1 = q - p + 1;
  int n2 = r - q;

  double L[n1];
  double R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[p + i];
  }

  for (j = 0; j < n2; j++) {
    R[i] = arr[q + j + 1];
  }

  i = 0;
  j = 0;
  k = p; // the beginning

  while (i < n1 && j < n2) {
    if (L[i] >= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (i < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void printVector(std::vector<double> arr) {
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << std::endl;
}

void merge_sort(std::vector<double> &arr, int p, int r) {
  if (p >= r) {
    return;
  }
  int q = p + (r - p) / 2; // mid point

  merge_sort(arr, p, q);
  merge_sort(arr, q + 1, r);

  merge(arr, p, r, q);
}

int main() {
  std::vector<double> arr;
  arr.push_back(2);
  arr.push_back(3);
  printVector(arr); 
  merge_sort(arr, 0, arr.size());

  printVector(arr);

  return 0;
}
