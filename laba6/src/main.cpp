#include "HashTable.h"
#include <iostream>

void printMenu() {
    std::cout << "\nHash Table Operations:\n";
    std::cout << "1. Insert key-value pair\n";
    std::cout << "2. Find by key\n";
    std::cout << "3. Remove by key\n";
    std::cout << "4. Print table\n";
    std::cout << "5. Print bucket contents\n";
    std::cout << "6. Print key info\n";
    std::cout << "7. Show statistics\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    size_t tableSize;
    std::cout << "Enter hash table size: ";
    std::cin >> tableSize;
    
    HashTable ht(tableSize);
    int choice;
    std::string key, value;
    
    do {
        printMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cout << "Enter value: ";
                std::cin >> value;
                if (ht.insert(key, value)) {
                    std::cout << "Inserted successfully.\n";
                } else {
                    std::cout << "Key already exists!\n";
                }
                break;
            }
            // Обработка остальных случаев
            // ...
        }
    } while (choice != 0);
    
    return 0;
}