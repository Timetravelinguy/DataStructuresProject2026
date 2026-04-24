#pragma once

#include <cstddef>
#include <deque>
#include <stdexcept>

namespace ds {

template <typename T>
class Queue {
public:
    void enqueue(const T& value);
    void dequeue();
    const T& front() const;
    bool empty() const;
    std::size_t size() const;

    // TODO(Person 1): Move front element to back k times.
    // Hint: k can be larger than size(), so use modulo when size > 0.
    void rotate(std::size_t k);

    // TODO(Person 1): Return true if front-to-back order is a palindrome.
    bool is_palindrome() const;

private:
    std::deque<T> data_;
};

template <typename T>
void Queue<T>::enqueue(const T& value) {
    data_.push_back(value);
}

template <typename T>
void Queue<T>::dequeue() {
    if (data_.empty()) {
        throw std::underflow_error("Cannot dequeue from an empty queue");
    }
    data_.pop_front();
}

template <typename T>
const T& Queue<T>::front() const {
    if (data_.empty()) {
        throw std::underflow_error("Cannot get front of an empty queue");
    }
    return data_.front();
}

template <typename T>
bool Queue<T>::empty() const {
    return data_.empty();
}

template <typename T>
std::size_t Queue<T>::size() const {
    return data_.size();
}

template <typename T>
void Queue<T>::rotate(std::size_t k) {
    throw std::logic_error("TODO(Person 1): implement Queue::rotate");
}

template <typename T>
bool Queue<T>::is_palindrome() const {
    throw std::logic_error("TODO(Person 1): implement Queue::is_palindrome");
}

}  // namespace ds
