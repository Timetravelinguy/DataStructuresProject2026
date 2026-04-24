#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class BinarySearchTree {
public:
    void insert(const T& value);
    bool contains(const T& value) const;

    // TODO(Person 3): Return sorted values using in-order traversal.
    std::vector<T> inorder() const;

    // TODO(Person 3): Return longest path length from root to leaf.
    std::size_t height() const;

    // TODO(Person 3): Remove a value from the tree.
    // Cases: leaf, one child, two children.
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
    throw std::logic_error("TODO(Person 3): implement BinarySearchTree::inorder");
}

template <typename T>
std::size_t BinarySearchTree<T>::height() const {
    throw std::logic_error("TODO(Person 3): implement BinarySearchTree::height");
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& value) {
    throw std::logic_error("TODO(Person 3): implement BinarySearchTree::remove");
}

}  // namespace ds
