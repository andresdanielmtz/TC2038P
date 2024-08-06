#include <iostream> 
#include <queue>

void showq(std::queue<int> gq) {
  std::queue<int> g = gq;
  while (!g.empty()) { 
    std::cout << "\t" << g.front(); 
    g.pop(); 
  }
  std::cout << "\n"; 
}

int main() {
  std::queue<int> qg;
  qg.push(10);
  qg.push(20);
  qg.push(30);

  showq(qg);

  qg.pop();

  showq(qg);

  std::cout << "Back \t" << qg.back() << std::endl; 
  qg.pop(); 

  showq(qg); 

  return 0;
}
