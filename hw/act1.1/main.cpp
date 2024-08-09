#include <iostream> 
#include <vector> 

// Andres Martinez
//  https://www.geeksforgeeks.org/merge-sort/
//  Introduction to Algorithms, MIT

void merge(std::vector<double> & arr, int p, int q, int r) {
  int n1 = q - p + 1;  // length of first half 
  int n2 = r - q; // length of second half

  double L[n1]; double R[n2];

  for (int i = 0; i < n1; i++) {
    L[i] = arr[p + i]; // Copy the first half 
  }

  for (int j = 0; j < n2; j++) {
    R[j] = arr[q + j + 1]; // Copy the second half
  }

  int i = 0; int j = 0; int k = p;

  while (i < n1 && j < n2) { 
    if (L[i] <= R[j]) { 
      arr[k] = L[i];
      i++;
    }
    else {
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

void merge_sort(std::vector<double> & arr, int p, int r) {
  // std::cout << "D:" << std::endl; 
  if (p >= r) {  // if there's one or no element
  return; 
  }

  int q = p + (r - p) / 2; // midpoint, used to avoid integer overflow 

  merge_sort(arr, p, q); // First half
  merge_sort(arr, q + 1, r);  // Second half

  merge(arr, p, q, r); 

}


void print_vector(std::vector<double> arr) { 
  int arr_size = arr.size();
  for (int i = 0; i < arr_size; i++) {
    std::cout << arr[i] << "\t"; 
  }
  std::cout << "\n";
}

int main() {
  std::vector<double> arr = {1,2,3,4};
  arr.resize(4); 
  print_vector(arr);


  int arr_size = arr.size(); 
  merge_sort(arr, 0, arr_size - 1);
  print_vector(arr); 
  return 0; 
}
