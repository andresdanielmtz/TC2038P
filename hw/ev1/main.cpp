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

std::vector<std::string> read_file(std::string file_name) {
  std::ifstream file;
  file.open(file_name);
  std::vector<std::string> string_content;
  std::string file_output;

  if (file.is_open()) {
    while (file >> file_output) {
      string_content.push_back(file_output);
    }
  }
  return string_content;
}

int main() {
  std::vector<std::string> transmission_one = read_file("transmission1.txt");
  std::vector<std::string> transmission_two = read_file("transmission2.txt");

  std::string mcode_one = read_file("mcode1.txt")[0];
  std::string mcode_two = read_file("mcode2.txt")[0];
  std::string mcode_three = read_file("mcode3.txt")[0];

  std::cout << mcode_one << std::endl;
  std::cout << mcode_two << std::endl;
  std::cout << mcode_three << std::endl;
}