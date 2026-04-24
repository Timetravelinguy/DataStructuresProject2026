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

    // TODO(Person 2): Add to end of list in O(n).
    void push_back(const T& value);

    // TODO(Person 2): Remove first node equal to value.
    // Return true if a node is removed, false otherwise.
    bool erase_first(const T& value);

    // TODO(Person 2): Return current list elements from head to tail.
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
    throw std::logic_error("TODO(Person 2): implement LinkedList::push_back");
}

template <typename T>
bool LinkedList<T>::erase_first(const T& value) {
    throw std::logic_error("TODO(Person 2): implement LinkedList::erase_first");
}

template <typename T>
std::vector<T> LinkedList<T>::to_vector() const {
    throw std::logic_error("TODO(Person 2): implement LinkedList::to_vector");
}

}  // namespace ds
