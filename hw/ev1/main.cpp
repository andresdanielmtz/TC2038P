#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool is_palindrome(std::string word) { // Two pointers approach
  int l = 0;
  int r = word.size() - 1;
  while (r >= l) {
    if (word[r] != word[l]) {
      return false;
    }
    l++;
    r--;
  }
  return true;
}

int main() {
  std::ifstream file;
  file.open("transmission1.txt");
  std::string file_output;
  std::vector<std::string> transmission_one;

  if (file.is_open()) {
    while (file >> file_output) {
      std::cout << file_output << std::endl;
      transmission_one.push_back(file_output);
    }
  }
  std::cout << "Vector content" << std::endl;

  for (std::string line : transmission_one) {
    std::cout << line << " ";
  }
  std::cout << std::endl;
}