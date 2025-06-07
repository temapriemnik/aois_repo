#include "AVLTree.h"
#include <algorithm>

void AVLTree::Node::updateHeight() {
    height = 1 + std::max(
        left ? left->height : 0,
        right ? right->height : 0
    );
}

int AVLTree::Node::getBalance() const {
    return (left ? left->height : 0) - (right ? right->height : 0);
}

// Реализация методов вращения, балансировки и CRUD операций
// ... (полная реализация всех методов из AVLTree.h)