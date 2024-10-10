#include <iostream>
#include <vector>

int kadaneAlgorithm(std::vector<int> lst) {
  if (lst.empty()) {
    return -1;
  }

  int res = lst[0];
  for (int i = 0; i < lst.size(); i++) {
    int currSum = 0;

    for (int j = i; j < lst.size(); j++) {
      currSum += lst[j];

      if (currSum > res) { // same as max() :)
        res = currSum;
      }
    }
  }
  return res;
}

void initialize_vector(std::vector<int> & arr ) { 
    arr.push_back(1); 
    arr.push_back(2); 
    arr.push_back(3); 
    arr.push_back(4); 
    arr.push_back(5); 
    arr.push_back(-100); 
    arr.push_back(10); 
    arr.push_back(10); 
    arr.push_back(10); 
}

int main() {
  std::vector<int> example_lst;
  initialize_vector(example_lst); 

  int result = kadaneAlgorithm(example_lst);
  std::cout << "The result is " << result << std::endl;
}