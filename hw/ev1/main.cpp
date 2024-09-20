#include <iostream>
#include <string>

bool is_palindrome(std::string word) {
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
  std::string word = "aba";
  bool result = is_palindrome(word); 
  std::cout << result << std::endl; 
  return 0;
}