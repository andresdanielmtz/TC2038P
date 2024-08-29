#include <iostream>
#include "HashTable.h"

int fib(int num, HashTable & memo) { 
    if (memo.search(num) != -1) { 
        return memo.search(num); 
    }
    if (num == 0) { 
        return 0; 
    }
    if (num == 1) { 
        return 1; 
    }
    memo.insert(num, fib(num - 1, memo) + fib(num - 2, memo));
    return memo.search(num);
}

int main() { 
    HashTable memo(10); 
    memo.insert(0, 0);
    memo.insert(1,1);
    
    for (int i = 0; i < 100; i++) { 
        std::cout << fib(i, memo) << std::endl; 
    }
    memo.displayTable();
}
