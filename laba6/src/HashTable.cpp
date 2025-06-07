#include "HashTable.h"
#include <iostream>

size_t HashTable::hashFunction(const std::string& key) const {
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
    }
    return hash;
}

HashTable::HashTable(size_t size) : capacity(size), buckets(size) {}

bool HashTable::insert(const std::string& key, const std::string& value) {
    if (find(key)) return false; // Ключ уже существует
    
    TableEntry entry(key, value);
    entry.V = std::hash<std::string>{}(key);
    entry.hV = hashFunction(key);
    
    if (buckets[entry.hV].insert(entry)) {
        itemCount++;
        return true;
    }
    return false;
}

// Реализация остальных методов HashTable
// ... (полная реализация всех методов из HashTable.h)