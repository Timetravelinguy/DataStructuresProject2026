#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace ds {

template <typename T>
class HashTable {
public:
    explicit HashTable(std::size_t bucket_count = 8);
    void insert(const T& value);
    bool contains(const T& value) const;
    bool erase(const T& value);
    std::size_t bucket_count() const;
    std::size_t size() const;

private:
    std::vector<std::vector<T>> buckets_;
    std::size_t size_ = 0;
    std::size_t bucket_index(const T& value) const;
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
    auto& bucket = buckets_[bucket_index(value)];
    for (const T& existing : bucket) {
        if (existing == value) {
            return;
        }
    }
    bucket.push_back(value);
    ++size_;
}

template <typename T>
bool HashTable<T>::contains(const T& value) const {
    const auto& bucket = buckets_[bucket_index(value)];
    for (const T& existing : bucket) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool HashTable<T>::erase(const T& value) {
    auto& bucket = buckets_[bucket_index(value)];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (*it == value) {
            bucket.erase(it);
            --size_;
            return true;
        }
    }
    return false;
}

template <typename T>
std::size_t HashTable<T>::bucket_count() const {
    return buckets_.size();
}

template <typename T>
std::size_t HashTable<T>::size() const {
    return size_;
}

}  // namespace ds
