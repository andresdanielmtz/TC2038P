#include <iostream>
#include <string>
#include <vector>

// Andres Martinez, A00227463

void merge(std::vector<double> &arr, int p, int q, int r) {
  int i, j, k;
  int n1 = q - p + 1;
  int n2 = r - q;

  double L[n1];
  double R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[p + i];
  }

  for (j = 0; j < n2; j++) {
    R[j] = arr[q + j + 1];
  }

  i = 0;
  j = 0;
  k = p;

  // Conquer
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

void merge_sort(std::vector<double> &arr, int p, int r) {
  if (p >= r) { // if there's one or no element
    return;
  }

  // Divide
  int q = p + (r - p) / 2; // midpoint, used to avoid integer overflow

  merge_sort(arr, p, q);
  merge_sort(arr, q + 1, r);

  // Combine
  merge(arr, p, q, r);
}

void print_vector(std::vector<double> arr) {
  int arr_size = arr.size();
  for (int i = 0; i < arr_size; i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << "\n";
}

void add_elements(std::vector<double> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    arr.push_back(i);
  }
}

int main() {
  int index = 0;
  int size_arr = 0;

  std::vector<double> arr;

  for (std::string line; std::getline(std::cin, line);) {
    if (index != 0) {
      arr.push_back(std::stod(line));
    }
    index++;
  }
  std::cout << "Array original: \t";
  print_vector(arr);

  int arr_size = arr.size();
  merge_sort(arr, 0, arr_size - 1);

  std::cout << "Array ordenado: \t";
  print_vector(arr);
  return 0;
}
