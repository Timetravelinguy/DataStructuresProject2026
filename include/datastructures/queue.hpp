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
    if (data_.empty()) {
        return;  // Nothing to rotate if queue is empty
    }
    
    k = k % data_.size();  // Handle k larger than size using modulo
    
    for (std::size_t i = 0; i < k; ++i) {
        T front_value = data_.front();  // Get front element
        data_.pop_front();               // Remove it from front
        data_.push_back(front_value);    // Add it to back
    }
}

template <typename T>
bool Queue<T>::is_palindrome() const {
    if (data_.empty() || data_.size() == 1) {
        return true;  // Empty or single-element queue is a palindrome
    }
    
    // Compare elements from both ends moving towards the center
    for (std::size_t i = 0; i < data_.size() / 2; ++i) {
        if (data_[i] != data_[data_.size() - 1 - i]) {
            return false;  // Mismatch found
        }
    }
    return true;  // All matches, it's a palindrome
}

}  // namespace ds