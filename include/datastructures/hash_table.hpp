#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

template <typename T>
class HashTable {
public:
    explicit HashTable(std::size_t bucket_count = 8);

    // TODO(Person 2): Insert value if it is not already present.
    void insert(const T& value);

    // TODO(Person 2): Return true if value exists in the table.
    bool contains(const T& value) const;

    // TODO(Person 2): Remove value if it exists and return whether removal happened.
    bool erase(const T& value);

    // TODO(Person 2): Return the current number of buckets.
    std::size_t bucket_count() const;

    // TODO(Person 2): Return the number of stored values.
    std::size_t size() const;

private:
    std::vector<std::vector<T>> buckets_;
    std::size_t size_ = 0;

    std::size_t bucket_index(const T& value) const;
    void maybe_rehash();
};

template <typename T>
HashTable<T>::HashTable(std::size_t bucket_count)
    : buckets_(bucket_count == 0 ? 8 : bucket_count) {}

template <typename T>
std::size_t HashTable<T>::bucket_index(const T& value) const {
    return std::hash<T>{}(value) % buckets_.size();
}

template <typename T>
void HashTable<T>::insert(const T& value) {
    throw std::logic_error("TODO(Person 2): implement HashTable::insert");
}

template <typename T>
bool HashTable<T>::contains(const T& value) const {
    throw std::logic_error("TODO(Person 2): implement HashTable::contains");
}

template <typename T>
bool HashTable<T>::erase(const T& value) {
    throw std::logic_error("TODO(Person 2): implement HashTable::erase");
}

template <typename T>
std::size_t HashTable<T>::bucket_count() const {
    return buckets_.size();
}

template <typename T>
std::size_t HashTable<T>::size() const {
    return size_;
}

template <typename T>
void HashTable<T>::maybe_rehash() {
    throw std::logic_error("TODO(Person 2): implement HashTable::maybe_rehash");
}

}  // namespace ds
