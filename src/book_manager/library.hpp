#pragma once

#include <string>
#include <vector>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/stack.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/hash_table.hpp"

struct Book {
    std::string title;
    std::string author;
    int year;

    Book() : title(""), author(""), year(0) {}
    Book(const std::string& t, const std::string& a, int y)
        : title(t), author(a), year(y) {}

    bool operator==(const Book& other) const {
        return title == other.title && author == other.author && year == other.year;
    }

    bool operator<(const Book& other) const {
        return year < other.year;
    }

    bool operator>(const Book& other) const {
        return year > other.year;
    }

    void display() const;
};

class LibraryManager {
public:
    LibraryManager();
    void init_sample();
    void run_cli();

private:
    void print_menu() const;
    static std::string to_lower(const std::string& s);

    ds::BinarySearchTree<Book> library_;
    ds::Stack<Book> recently_viewed_;
    ds::Queue<Book> checkout_queue_;
    ds::LinkedList<Book> wishlist_;
    ds::HashTable<int> isbn_db_;
};
