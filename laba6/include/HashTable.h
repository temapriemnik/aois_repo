#pragma once
#include "AVLTree.h"

class HashTable {
private:
    std::vector<AVLTree> buckets;
    size_t capacity;
    size_t itemCount = 0;

    // Хеш-функция по варианту
    size_t hashFunction(const std::string& key) const;
    
public:
    explicit HashTable(size_t size = 10);
    
    // Основные операции
    bool insert(const std::string& key, const std::string& value);
    bool remove(const std::string& key);
    TableEntry* find(const std::string& key) const;
    
    // Статистика
    double loadFactor() const;
    size_t collisionsCount() const;
    size_t size() const { return itemCount; }
    size_t capacity() const { return capacity; }
    
    // Вывод информации
    void print() const;
    void printBucket(size_t index) const;
    void printKeyInfo(const std::string& key) const;
};