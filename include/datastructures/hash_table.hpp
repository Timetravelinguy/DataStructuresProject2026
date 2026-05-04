#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>

namespace ds {

template <typename T>
class HashTable {
private:
    // Node for separate chaining
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

public:
    explicit HashTable(std::size_t bucket_count = 8);
    ~HashTable();

    // Copying not supported (manual memory management)
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(const T& value);
    bool contains(const T& value) const;
    bool erase(const T& value);
    std::size_t bucket_count() const;
    std::size_t size() const;

private:
    Node** buckets_;            // Dynamic array of bucket head pointers
    std::size_t bucket_count_;  // Number of buckets
    std::size_t size_;          // Total number of elements

    std::size_t bucket_index(const T& value) const;
};

// Constructor: allocate dynamic bucket array
template <typename T>
HashTable<T>::HashTable(std::size_t bucket_count)
    : bucket_count_(bucket_count == 0 ? 8 : bucket_count), size_(0) {
    buckets_ = new Node*[bucket_count_];
    for (std::size_t i = 0; i < bucket_count_; ++i) {
        buckets_[i] = nullptr;
    }
}

// Destructor: deallocate all nodes and bucket array
template <typename T>
HashTable<T>::~HashTable() {
    for (std::size_t i = 0; i < bucket_count_; ++i) {
        Node* current = buckets_[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] buckets_;
}

// Compute bucket index for a value
template <typename T>
std::size_t HashTable<T>::bucket_index(const T& value) const {
    return std::hash<T>{}(value) % bucket_count_;
}

// Insert a value (no duplicates)
template <typename T>
void HashTable<T>::insert(const T& value) {
    std::size_t idx = bucket_index(value);
    Node* current = buckets_[idx];

    // Check if value already exists
    while (current != nullptr) {
        if (current->data == value) {
            return;  // Duplicate, don't insert
        }
        current = current->next;
    }

    // Insert at the head of the bucket chain
    Node* new_node = new Node(value);
    new_node->next = buckets_[idx];
    buckets_[idx] = new_node;
    ++size_;
}

// Check if value exists
template <typename T>
bool HashTable<T>::contains(const T& value) const {
    std::size_t idx = bucket_index(value);
    Node* current = buckets_[idx];

    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Remove a value (returns true if found and removed)
template <typename T>
bool HashTable<T>::erase(const T& value) {
    std::size_t idx = bucket_index(value);
    Node* current = buckets_[idx];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            // Found it, remove from chain
            if (prev == nullptr) {
                buckets_[idx] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            --size_;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;  // Not found
}

template <typename T>
std::size_t HashTable<T>::bucket_count() const {
    return bucket_count_;
}

template <typename T>
std::size_t HashTable<T>::size() const {
    return size_;
}

}  // namespace ds
