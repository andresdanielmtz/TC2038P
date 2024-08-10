#include <iostream>
#include <vector>

int partition(std::vector<double> &arr, int l, int r) {
  int x = arr[l];
  int i = l - 1;

  for (int j = l; j < r - 1; j++) {
    if (arr[j] <= x) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[r]);
  return i + 1;
}

void quick_sort(std::vector<double> &arr, int l, int r) {
  int q = partition(arr, l, r);

  quick_sort(arr, 0, q - 1);
  quick_sort(arr, q + 1, r - l);
}

void printArray(std::vector<double> arr) {
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<double> arr;
  arr.push_back(2);
  arr.push_back(1);
  arr.push_back(30);
  printArray(arr);

  quick_sort(arr, 0, arr.size());
}
