#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    void insert(const T& value);
    bool contains(const T& value) const;
    std::vector<T> inorder() const;
    std::size_t height() const;
    bool remove(const T& value);

private:
    struct Node {
        T value;
        Node* left;
        Node* right;
    };

    Node* root_ = nullptr;
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    auto destroy = [&](auto&& self, Node* node) -> void {
        if (node == nullptr) return;
        self(self, node->left);
        self(self, node->right);
        delete node;
    };
    destroy(destroy, root_);
    root_ = nullptr;
}

template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    Node** current = &root_;
    while (*current != nullptr) {
        if (value < (*current)->value) {
            current = &(*current)->left;
        } else if (value > (*current)->value) {
            current = &(*current)->right;
        } else {
            return;
        }
    }
    *current = new Node{value, nullptr, nullptr};
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& value) const {
    Node* current = root_;
    while (current != nullptr) {
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            return true;
        }
    }
    return false;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::inorder() const {
    std::vector<T> values;
    auto traverse = [&](auto&& self, Node* node) -> void {
        if (node == nullptr) return;
        self(self, node->left);
        values.push_back(node->value);
        self(self, node->right);
    };
    traverse(traverse, root_);
    return values;
}

template <typename T>
std::size_t BinarySearchTree<T>::height() const {
    auto compute = [&](auto&& self, Node* node) -> std::size_t {
        if (node == nullptr) return 0;
        std::size_t left = self(self, node->left);
        std::size_t right = self(self, node->right);
        return 1 + (left > right ? left : right);
    };
    return compute(compute, root_);
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& value) {
    Node** ptr = &root_;
    while (*ptr != nullptr) {
        if (value < (*ptr)->value) {
            ptr = &(*ptr)->left;
        } else if (value > (*ptr)->value) {
            ptr = &(*ptr)->right;
        } else {
            Node* node = *ptr;
            if (node->left == nullptr) {
                *ptr = node->right;
                delete node;
                return true;
            }
            if (node->right == nullptr) {
                *ptr = node->left;
                delete node;
                return true;
            }
            Node** succ_ptr = &node->right;
            while ((*succ_ptr)->left != nullptr) {
                succ_ptr = &(*succ_ptr)->left;
            }
            Node* succ = *succ_ptr;
            node->value = succ->value;
            *succ_ptr = succ->right;
            delete succ;
            return true;
        }
    }
    return false;
}

}  // namespace ds
