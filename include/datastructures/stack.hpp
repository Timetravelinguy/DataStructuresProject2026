#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>

namespace ds {

template <typename T>
class Stack {
public:
    static constexpr std::size_t npos = std::numeric_limits<std::size_t>::max();

    Stack() = default;
    ~Stack();

    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
    std::size_t size() const;
    bool contains(const T& value) const;
    std::size_t index_of(const T& value) const;
    void reverse();

private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v, Node* n) : value(v), next(n) {}
    };

    Node* head_ = nullptr; // top of stack
    std::size_t size_ = 0;
};

template <typename T>
Stack<T>::~Stack() {
    Node* cur = head_;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head_ = nullptr;
    size_ = 0;
}

template <typename T>
void Stack<T>::push(const T& value) {
    head_ = new Node(value, head_);
    ++size_;
}

template <typename T>
void Stack<T>::pop() {
    if (head_ == nullptr) {
        throw std::underflow_error("Cannot pop from an empty stack");
    }
    Node* removed = head_;
    head_ = head_->next;
    delete removed;
    --size_;
}

template <typename T>
const T& Stack<T>::top() const {
    if (head_ == nullptr) {
        throw std::underflow_error("Cannot get top of an empty stack");
    }
    return head_->value;
}

template <typename T>
bool Stack<T>::empty() const {
    return head_ == nullptr;
}

template <typename T>
std::size_t Stack<T>::size() const {
    return size_;
}

template <typename T>
bool Stack<T>::contains(const T& value) const {
    for (Node* cur = head_; cur != nullptr; cur = cur->next) {
        if (cur->value == value) return true;
    }
    return false;
}

template <typename T>
std::size_t Stack<T>::index_of(const T& value) const {
    // Return index from bottom (0-based) to match previous API.
    std::size_t i = 0;
    for (Node* cur = head_; cur != nullptr; cur = cur->next, ++i) {
        if (cur->value == value) {
            return (size_ == 0) ? npos : (size_ - 1 - i);
        }
    }
    return npos;
}

template <typename T>
void Stack<T>::reverse() {
    Node* prev = nullptr;
    Node* cur = head_;
    while (cur != nullptr) {
        Node* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head_ = prev;
}

}  // namespace ds
