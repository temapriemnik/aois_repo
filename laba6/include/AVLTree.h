#pragma once
#include "common.h"

class AVLTree {
private:
    struct Node {
        TableEntry data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height;

        Node(const TableEntry& entry) 
            : data(entry), left(nullptr), right(nullptr), height(1) {}
        
        void updateHeight();
        int getBalance() const;
    };

    std::unique_ptr<Node> root;

    // Балансировка
    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> y);
    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> x);
    std::unique_ptr<Node> balance(std::unique_ptr<Node> node);
    
    // Вспомогательные методы
    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const TableEntry& entry);
    bool remove(std::unique_ptr<Node>& node, const std::string& key);
    Node* find(Node* node, const std::string& key) const;
    void traverse(Node* node, std::vector<TableEntry>& entries) const;

public:
    AVLTree() = default;
    
    // CRUD операции
    bool insert(const TableEntry& entry);
    bool remove(const std::string& key);
    TableEntry* find(const std::string& key) const;
    std::vector<TableEntry> getAllEntries() const;
    
    // Информация
    size_t size() const;
    size_t height() const;
};