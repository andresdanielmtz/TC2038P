/**
 * @file main.cpp
 * @author Andrés Martínez (A00227463@tec.mx)
 * @brief evidencia 1, Análisis de Algoritmos Avanzados
 * @version 0.1
 * @date 2024-09-26
 *
 * @copyright Copyright (c) 2024
 *
 */

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

std::vector<std::string> read_file_lines(const std::string &filename) {
  std::ifstream file(filename);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
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

  for (std::string word : words) {
    bool checker = false; 
    for (std::string str : str_vector) {
      if (str.find(word) != std::string::npos) {  
        checker = true;
        break;  
      }
    }
    if (checker) {
      std::cout << "True\t" << word << std::endl;
    } else {
      std::cout << "False\t" << word << std::endl;
    }
  }
}


void print_vector(std::vector<std::string> vec) {
  for (std::string elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

std::string split(std::string word, int l, int r) {
  std::string result = "";
  for (int i = l; i <= r; i++) {
    result = result + word[i];
  }
  return result;
}

std::pair<int, int>
longest_palindrome(const std::vector<std::string> &content) {
  std::string longest_pal = "";
  int longest_start = 0;
  int longest_end = 0;
  int total_length = 0;

  for (const std::string &word : content) {
    int word_length = word.length();
    for (int l = 0; l < word_length; l++) {
      for (int r = l; r < word_length; r++) {
        std::string word_in_range = split(word, l, r);
        if (is_palindrome(word_in_range) &&
            word_in_range.length() > longest_pal.length()) {
          longest_pal = word_in_range;
          longest_start = total_length + l;
          longest_end = total_length + r;
        }
      }
    }
    total_length += word_length + 1;
  }
  return std::make_pair(longest_start, longest_end);
}

std::string longest_common_substring(const std::string &str1,
                                     const std::string &str2) {
  int len1 = str1.length();
  int len2 = str2.length();
  std::string longest_substr = "";

  for (int i = 0; i < len1; i++) {
    for (int j = 0; j < len2; j++) {
      int match_length = 0;
      while (i + match_length < len1 && j + match_length < len2 &&
             str1[i + match_length] == str2[j + match_length]) {
        match_length++;
      }
      if (match_length > longest_substr.length()) {
        longest_substr = str1.substr(i, match_length);
      }
    }
  }

  return longest_substr;
}

std::string find_longest_common_substring_in_files(const std::string &file1,
                                                   const std::string &file2) {
  std::vector<std::string> lines1 = read_file_lines(file1);
  std::vector<std::string> lines2 = read_file_lines(file2);

  std::string longest_substring;

  for (const std::string &line1 : lines1) {
    for (const std::string &line2 : lines2) {
      std::string common = longest_common_substring(line1, line2);
      if (common.length() > longest_substring.length()) {
        longest_substring = common;
      }
    }
  }

  return longest_substring;
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

  std::cout << "PART 1" << std::endl;
  is_substrs_in_str(transmission_one, word_vector);
  is_substrs_in_str(transmission_two, word_vector);

  std::cout << "PART 2" << std::endl;
  std::pair<int, int> result_one = longest_palindrome(transmission_one);
  std::cout << "Start index: " << result_one.first
            << ", End index: " << result_one.second << std::endl;

  std::pair<int, int> result_two = longest_palindrome(transmission_two);
  std::cout << "Start index: " << result_two.first
            << ", End index: " << result_two.second << std::endl;

  std::cout << "PART 3" << std::endl;
  std::string lcs = find_longest_common_substring_in_files("transmission1.txt",
                                                           "transmission2.txt");

  std::cout << "The longest common substring is: " << lcs << std::endl;
  std::cout << "Its length is: " << lcs.length() << std::endl;
}
