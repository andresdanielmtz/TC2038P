#include <iostream>
#include <vector>

// Andrés Martínez, A00227463
// https://www.geeksforgeeks.org/merge-sort/

void merge(std::vector<double> &arr, int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  double L[n1]; // Two Arrays (empty), one the size of the first half and the
                // other with the size of the other size.
  double R[n2];

  for (int i = 0; i < n1; i++) // Add each element of the left to the L[] arr
    L[i] = arr[l + i];
  for (int j = 0; j < n2; j++) // Same goes for the R[] arr
    R[j] = arr[m + 1 + j];

  int i = 0, j = 0;
  int k = l;

  while ((i < n1) && (j < n2)) {
    if (L[i] >= R[j]) { // If value from the L is equal or higher than the one
                        // on the right
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
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<double> &arr, int l, int r) {
  std::cout << ":D" << std::endl;
  if (l >= r) {
    return;
  }
  int m = l + (r - l) / 2;

  mergeSort(arr, l, m);
  mergeSort(arr, m + 1, r);
  merge(arr, l, m, r);
}

void print_arr(std::vector<double> arr) {
  int arr_size = arr.size();
  for (int i = 0; i < arr_size; i++) {
    std::cout << arr[i] << "\t";
  }
}

int main() {
  int n, i, input;
  std::vector<double> arr;
  arr.resize(10);
  for (i = 0; i < 10; i++) {
    arr[i] = 10 - i;
  }
  int arr_size = arr.size();

  mergeSort(arr, 0, arr_size - 1);

  std::cout << "Print Final Array" << std::endl;
  print_arr(arr);

  return 0;
}