#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class Queue {
public:
    Queue() = default;
    ~Queue();

    void enqueue(const T& value);
    void dequeue();
    const T& front() const;
    bool empty() const;
    std::size_t size() const;
    void rotate(std::size_t k);
    bool is_palindrome() const;

private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head_ = nullptr; // front
    Node* tail_ = nullptr; // back
    std::size_t size_ = 0;
};

template <typename T>
Queue<T>::~Queue() {
    Node* cur = head_;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    Node* n = new Node(value);
    if (tail_ == nullptr) {
        head_ = tail_ = n;
    } else {
        tail_->next = n;
        tail_ = n;
    }
    ++size_;
}

template <typename T>
void Queue<T>::dequeue() {
    if (head_ == nullptr) {
        throw std::underflow_error("Cannot dequeue from an empty queue");
    }
    Node* removed = head_;
    head_ = head_->next;
    if (head_ == nullptr) tail_ = nullptr;
    delete removed;
    --size_;
}

template <typename T>
const T& Queue<T>::front() const {
    if (head_ == nullptr) {
        throw std::underflow_error("Cannot get front of an empty queue");
    }
    return head_->value;
}

template <typename T>
bool Queue<T>::empty() const {
    return head_ == nullptr;
}

template <typename T>
std::size_t Queue<T>::size() const {
    return size_;
}

template <typename T>
void Queue<T>::rotate(std::size_t k) {
    if (size_ == 0) return;
    k = k % size_;
    for (std::size_t i = 0; i < k; ++i) {
        Node* n = head_;
        head_ = head_->next;
        n->next = nullptr;
        if (tail_) tail_->next = n;
        tail_ = n;
        if (head_ == nullptr) head_ = tail_;
    }
}

template <typename T>
bool Queue<T>::is_palindrome() const {
    if (size_ <= 1) return true;
    std::vector<T> v;
    v.reserve(size_);
    for (Node* cur = head_; cur != nullptr; cur = cur->next) v.push_back(cur->value);
    for (std::size_t i = 0; i < v.size() / 2; ++i) if (v[i] != v[v.size() - 1 - i]) return false;
    return true;
}

}  // namespace ds
