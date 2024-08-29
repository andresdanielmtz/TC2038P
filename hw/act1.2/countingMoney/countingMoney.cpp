#include "HashTable.h"
#include "HashVector.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <string> 

HashTable::HashTable(int s) : size(s), numElements(0) {
    table.resize(size, std::make_pair(-1, -1));
}

int HashTable::hashFunction(int key) const {
    return std::abs(key) % size;
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(numElements) / size;
}

void HashTable::insert(int key, int value) {
    if (getLoadFactor() > 0.8) {
        resize(size * 2);
    }

    int index = hashFunction(key);
    while (table[index].first != -1 && table[index].first != key) {
        index = (index + 1) % size;
    }

    if (table[index].first == -1) {
        numElements++;
    }
    table[index].first = key;
    table[index].second = value;
}

int HashTable::search(int key) const {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (table[index].first == key) {
            return table[index].second;
        }
        index = (index + 1) % size;
    } while (index != startIndex && table[index].first != -1);

    return -1;  // Key not found
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (table[index].first == key) {
            table[index] = std::make_pair(-1, -1);
            numElements--;
            return;
        }
        index = (index + 1) % size;
    } while (index != startIndex && table[index].first != -1);
}

void HashTable::resize(int new_size) {
    std::vector<std::pair<int, int> > old_table = std::move(table);
    table.resize(new_size, std::make_pair(-1, -1));
    size = new_size;
    numElements = 0;

    for (const auto& entry : old_table) {
        if (entry.first != -1) {
            insert(entry.first, entry.second);
        }
    }
}

void HashTable::displayTable() const {
    for (int i = 0; i < size; i++) {
        if (table[i].first != -1) {
            std::cout << "Index " << i << ": Key = " << table[i].first 
                      << ", Value = " << table[i].second << std::endl;
        }
    }
}

int HashTable::getHashTableSize() { 
    return size;
}

void HashTable::modify(int key, int value) { 
    table[key].first = key;
    table[key].second = value; 
}

HashVector::HashVector(int s) : size(s), numElements(0) {
    table.resize(size);
}

HashVector::~HashVector() {

}

int HashVector::hashFunction(int key) const {
    return key % size;
}

double HashVector::getLoadFactor() const {
    return static_cast<double>(numElements) / size;
}

void HashVector::insert(int key, const std::vector<int>& values) {
    int index = hashFunction(key);
    for (int i = 0; i < size; i++) {
        int j = (index + i) % size;
        if (table[j].first == 0 || table[j].first == key) {
            table[j] = std::make_pair(key, values);
            numElements++;
            if (getLoadFactor() > 0.7) {
                resize(size * 2);
            }
            return;
        }
    }
}

std::vector<int> HashVector::search(int key) const {
    int index = hashFunction(key);
    for (int i = 0; i < size; i++) {
        int j = (index + i) % size;
        if (table[j].first == key) {
            return table[j].second;
        }
        if (table[j].first == 0) {
            break;
        }
    }
    return {};
}

void HashVector::remove(int key) {
    int index = hashFunction(key);
    for (int i = 0; i < size; i++) {
        int j = (index + i) % size;
        if (table[j].first == key) {
            table[j] = std::make_pair(0, std::vector<int>());
            numElements--;
            return;
        }
        if (table[j].first == 0) {
            break;
        }
    }
}

void HashVector::displayTable() const {
    for (int i = 0; i < size; i++) {
        if (table[i].first != 0) {
            std::cout << "Key: " << table[i].first << ", Values: ";
            for (int val : table[i].second) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
}

int HashVector::getHashTableSize() const {
    return size;
}

void HashVector::modify(int key, const std::vector<int>& values) {
    int index = hashFunction(key);
    for (int i = 0; i < size; i++) {
        int j = (index + i) % size;
        if (table[j].first == key) {
            table[j].second = values;
            return;
        }
        if (table[j].first == 0) {
            break;
        }
    }
}

void HashVector::resize(int new_size) {
    std::vector<std::pair<int, std::vector<int>>> old_table = table;
    table.clear();
    table.resize(new_size);
    size = new_size;
    numElements = 0;

    for (const auto& entry : old_table) {
        if (entry.first != 0) {
            insert(entry.first, entry.second);
        }
    }
}

int get_optimal_denomination(int remaining, HashTable& denominations) {
    for (int i = denominations.getHashTableSize() - 1; i >= 0; i--) {
        if (i <= remaining && denominations.search(i) > 0) {
            return i;
        }
    }
    return 0;
}

bool verify_prices(const std::vector<int>& arr, HashTable& denominations) {
    HashTable temp = denominations;
    for (int coin : arr) {
        int count = temp.search(coin);
        if (count <= 0) {
            return false;
        }
        temp.insert(coin, count - 1);
    }
    return true;
}

std::vector<int> calculate_change(int remaining, HashTable& denominations, HashVector& memo) {
    if (remaining == 0) {
        return {};
    }
    std::vector<int> memoized = memo.search(remaining);
    if (!memoized.empty()) {
        if (verify_prices(memoized, denominations)) {
            return memoized;
        }
    }

    int optimal = get_optimal_denomination(remaining, denominations);
    if (optimal == 0) {
        return {};
    }


    int count = denominations.search(optimal);
    denominations.insert(optimal, count - 1);
    
    std::vector<int> result = calculate_change(remaining - optimal, denominations, memo);
    result.insert(result.begin(), optimal);

    if (std::accumulate(result.begin(), result.end(), 0) == remaining) {
        memo.insert(remaining, result);
        return result;
    } else {
        std::cout << "Lo siento, pero no hay cambio suficiente :(" << std::endl;
        denominations.insert(optimal, count); // Backtrack
        return {};
    }
}

std::vector<int> greedy_change(int amount, HashTable& denominations) {
    std::vector<int> result;
    std::vector<int> available_denominations;

    // Agarramos todas las denominaciones disponibles (en Python esto se hace con un for loop)
    for (int i = 0; i < denominations.getHashTableSize(); i++) {
        if (denominations.search(i) > 0) {
            available_denominations.push_back(i);
        }
    }

    // Para todos los disponibles, los ordenamos en orden descendente (500, 200, 100, 50, 20, 10, 5, 2, 1)
    std::sort(available_denominations.begin(), available_denominations.end(), std::greater<int>());

    for (int coin : available_denominations) {
        while (amount >= coin && denominations.search(coin) > 0) {
            result.push_back(coin);
            amount -= coin;
            denominations.insert(coin, denominations.search(coin) - 1); 
            // Solamente decrementamos la cantidad de monedas en la tabla de hash basado en la denominación, también actualiza la Hash Table 
        }
    }

    if (amount > 0) {
        std::cout << "Lo siento, pero no hay cambio suficiente :(" << std::endl;
        return {};
    }

    return result;
}

void testing_algorithms(int target_change, HashTable& denominations, HashVector& memo) {
    std::vector<int> result = calculate_change(target_change, denominations, memo);
    std::cout << "Result 1: ";
    for (int coin : result) {
        std::cout << coin << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> result_2 = calculate_change(target_change, denominations, memo);
    std::cout << "Result 2: ";
    for (int coin : result_2) {
        std::cout << coin << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> result_3 = calculate_change(target_change, denominations, memo);
    std::cout << "Result 3: ";
    for (int coin : result_3) {
        std::cout << coin << " ";
    }
    std::cout << std::endl;

    std::vector<int> result_4 = greedy_change(50, denominations);
    std::cout << "Result 4: ";
    for (int coin : result_4) {
        std::cout << coin << " ";
    }
    std::cout << std::endl;

}

void setup_denominations(std::vector<int>& denominations, std::vector<int> amounts) {
    for (int i = 0; i < amounts.size(); i++) {
        denominations.push_back(amounts[i]);
    }
}

int main() {
    const std::vector<int> fixed_denominations = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    const int EXPECTED_N = 9; 

    int N;
    std::cin >> N;

    if (N != EXPECTED_N) {
        std::cout << "Error: Expected " << EXPECTED_N << " denominations, but got " << N << std::endl;
        return 1;
    }

    HashTable denominations(501); 


    for (int i = 0; i < N; i++) {
        int coin_count;
        std::cin >> coin_count;
        denominations.insert(fixed_denominations[i], coin_count);
    }

    int P, Q;
    std::cin >> P >> Q;

    int change_amount = Q - P;

    HashVector memo(change_amount + 1);


    std::vector<int> dp_result = calculate_change(change_amount, denominations, memo);

    std::cout << "Dynamic Programming Result: ";
    for (int value : dp_result) {
        std::cout << value << " "; 
    }
    std::cout << std::endl;
    std::vector<int> greedy_result = greedy_change(change_amount, denominations);

    std::cout << "Greedy Result: ";

    for (int value : greedy_result) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;

    return 0;
}