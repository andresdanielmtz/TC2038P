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

std::vector<std::string>
find_all_palindromes(const std::vector<std::string> &content) {
  std::vector<std::string> palindromes;

  for (const std::string &word : content) {
    int word_length = word.length();
    for (int l = 0; l < word_length; l++) {
      for (int r = l; r < word_length; r++) {
        std::string word_in_range = split(word, l, r);
        if (is_palindrome(word_in_range) && word_in_range.length() > 1) {
          palindromes.push_back(word_in_range);
        }
      }
    }
  }
  return palindromes;
}

std::string longest_common_palindrome(std::vector<std::string> arr_one,
                                      std::vector<std::string> arr_two) {
  std::string lcp = ""; // lcp = longest common palindrome
  for (std::string elem_one : arr_one) {
    for (std::string elem_two : arr_two) {
      if ((elem_one == elem_two) && (elem_one.length() > lcp.length())) {
        lcp = elem_one;
      }
    }
  }
  return lcp;
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
  std::vector<std::string> transmission_one_palindromes =
      find_all_palindromes(transmission_one);
  std::vector<std::string> transmission_two_palindromes =
      find_all_palindromes(transmission_two);

  std::string lcp = longest_common_palindrome(transmission_one_palindromes,
                                              transmission_two_palindromes);
  std::cout << "The longest common palindrome within these two files is: "
            << lcp << std::endl;
}
