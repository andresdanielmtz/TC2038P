#include <iostream>
#include <vector>

void merge(std::vector<double> &arr, int start, int end, int mid) {
  int i, j, k;
  int n1 = mid - start + 1;
  int n2 = end - mid;

  double L[n1];
  double R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[start + i];
  }

  for (j = 0; j < n2; j++) {
    R[i] = arr[mid + j + 1];
  }

  i = 0;
  j = 0;
  k = start; // the beginning

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

void merge_sort(std::vector<double> &arr, int start, int end) {
  if (start >= end) {
    return;
  }
  int q = start + (end - start) / 2; // mid point

  merge_sort(arr, start, q);
  merge_sort(arr, q + 1, end);

  merge(arr, start, end, q);
}

int main() {
  std::vector<double> arr;
  for (int i = 100; i > 0; i--) {
    arr.push_back(i);
  }
  
  printVector(arr); 
  merge_sort(arr, 0, arr.size());

  printVector(arr);

  return 0;
}
