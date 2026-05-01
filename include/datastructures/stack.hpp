#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class Stack {
public:
    static constexpr std::size_t npos = std::numeric_limits<std::size_t>::max();

    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
    std::size_t size() const;
    bool contains(const T& value) const;
    std::size_t index_of(const T& value) const;
    void reverse();

private:
    std::vector<T> data_;
};

template <typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (data_.empty()) {
        throw std::underflow_error("Cannot pop from an empty stack");
    }
    data_.pop_back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (data_.empty()) {
        throw std::underflow_error("Cannot get top of an empty stack");
    }
    return data_.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return data_.empty();
}

template <typename T>
std::size_t Stack<T>::size() const {
    return data_.size();
}

template <typename T>
bool Stack<T>::contains(const T& value) const {
    for (const T& item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::size_t Stack<T>::index_of(const T& value) const {
    for (std::size_t i = 0; i < data_.size(); ++i) {
        if (data_[i] == value) {
            return i;
        }
    }
    return npos;
}

template <typename T>
void Stack<T>::reverse() {
    std::reverse(data_.begin(), data_.end());
}

}  // namespace ds