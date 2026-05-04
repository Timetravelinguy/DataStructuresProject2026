#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/stack.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/hash_table.hpp"

enum class BookStatus {
    Available,
    Borrowed,
};

struct Book {
    long long isbn;
    std::string title;
    std::string author;
    int year;
    std::string category;
    BookStatus status;

    Book()
        : isbn(0), title(""), author(""), year(0), category("General"), status(BookStatus::Available) {}
    Book(long long i, const std::string& t, const std::string& a, int y,
         const std::string& c = "General",
         BookStatus s = BookStatus::Available)
        : isbn(i), title(t), author(a), year(y), category(c), status(s) {}

    bool operator==(const Book& other) const {
        return isbn == other.isbn && title == other.title && author == other.author && year == other.year && category == other.category && status == other.status;
    }

    bool operator<(const Book& other) const {
        if (year != other.year) return year < other.year;
        if (title != other.title) return title < other.title;
        if (author != other.author) return author < other.author;
        return isbn < other.isbn;
    }

    bool operator>(const Book& other) const {
        return other < *this;
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
    void print_help() const;
    static std::string to_lower(const std::string& s);
    void load_or_seed_storage();
    bool load_from_disk();
    void save_to_disk() const;
    bool load_queue_from_disk();
    void save_queue_to_disk() const;
    void seed_sample_books();
    bool find_book_by_isbn(long long isbn, Book& out) const;
    bool remove_book_by_isbn(long long isbn, Book& removed);
    bool set_book_status(long long isbn, BookStatus new_status, std::string& message);

    ds::BinarySearchTree<Book> library_;
    ds::Stack<Book> recently_viewed_;
    ds::Queue<Book> checkout_queue_;
    ds::LinkedList<Book> wishlist_;
    ds::HashTable<long long> isbn_db_;
    bool storage_ready_;
};
