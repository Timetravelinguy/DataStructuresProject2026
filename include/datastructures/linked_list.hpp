#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class LinkedList {
public:
    void push_front(const T& value);
    bool empty() const;
    std::size_t size() const;
    void push_back(const T& value);
    bool erase_first(const T& value);
    std::vector<T> to_vector() const;

private:
    struct Node {
        T value;
        Node* next;
    };

    Node* head_ = nullptr;
    std::size_t size_ = 0;
};

template <typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* new_node = new Node{value, head_};
    head_ = new_node;
    ++size_;
}

template <typename T>
bool LinkedList<T>::empty() const {
    return head_ == nullptr;
}

template <typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node{value, nullptr};

    if (head_ == nullptr) {
        head_ = new_node;
        ++size_;
        return;
    }

    Node* current = head_;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = new_node;
    ++size_;
}

template <typename T>
bool LinkedList<T>::erase_first(const T& value) {
    Node** current = &head_;
    while (*current != nullptr) {
        if ((*current)->value == value) {
            Node* removed = *current;
            *current = removed->next;
            delete removed;
            --size_;
            return true;
        }
        current = &(*current)->next;
    }
    return false;
}

template <typename T>
std::vector<T> LinkedList<T>::to_vector() const {
    std::vector<T> values;
    values.reserve(size_);
    Node* current = head_;
    while (current != nullptr) {
        values.push_back(current->value);
        current = current->next;
    }
    return values;
}

}  // namespace ds
