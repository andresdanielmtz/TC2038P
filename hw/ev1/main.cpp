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

bool in_word(std::string substr, std::string str) {
  return str.find(substr) != std::string::npos;
} // lol

void is_substrs_in_str(std::vector<std::string> str_vector,
                       std::vector<std::string> words) {

  bool checker = false;
  for (std::string word : words) {
    for (std::string str : str_vector) {
      if (in_word(word, str)) {
        checker = true;
      }
    }
    if (checker == true) {
      std::cout << "True" << word << std::endl;
    } else {
      std::cout << "False" << word << std::endl;
    }
  }
}

void print_vector(std::vector<std::string> vec) {
  for (std::string elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<std::string> transmission_one = read_file("transmission1.txt");
  std::vector<std::string> transmission_two = read_file("transmission2.txt");

  std::string mcode_one = read_file("mcode1.txt")[0];
  std::string mcode_two = read_file("mcode2.txt")[0];
  std::string mcode_three = read_file("mcode3.txt")[0];
  std::vector<std::string> word_vector;
  word_vector.push_back(mcode_one);
  word_vector.push_back(mcode_two);
  word_vector.push_back(mcode_three);

  is_substrs_in_str(transmission_one, word_vector);
  is_substrs_in_str(transmission_two, word_vector);
}