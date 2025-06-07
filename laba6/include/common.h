#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

struct TableEntry {
    std::string key;
    std::string value;
    int V = 0;         // Числовое значение ключа
    size_t hV = 0;     // Хеш-адрес
    
    TableEntry(const std::string& k, const std::string& v) 
        : key(k), value(v) {}
};