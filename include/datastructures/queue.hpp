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
    void rotate(std::size_t k);
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
        return;
    }

    k = k % data_.size();

    for (std::size_t i = 0; i < k; ++i) {
        T front_value = data_.front();
        data_.pop_front();
        data_.push_back(front_value);
    }
}

template <typename T>
bool Queue<T>::is_palindrome() const {
    if (data_.empty() || data_.size() == 1) {
        return true;
    }

    for (std::size_t i = 0; i < data_.size() / 2; ++i) {
        if (data_[i] != data_[data_.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

}  // namespace ds