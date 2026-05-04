#pragma once

#include <cstddef>
#include <iosfwd>
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

std::ostream& operator<<(std::ostream& os, const Book& book);

class LibraryManager {
public:
    LibraryManager();
    void run_cli();
    bool add_book(const Book& book, std::string& message);
    bool remove_book(long long isbn, Book& removed);
    bool search_by_id(long long isbn, Book& out) const;
    std::vector<Book> search_by_title_or_category(const std::string& query) const;
    std::vector<Book> list_books() const;
    bool borrow_book(long long isbn, std::string& message);
    bool return_book(long long isbn, std::string& message);

private:
    void print_menu() const;
    void print_help() const;
    void handle_add_book();
    void handle_remove_book();
    void handle_view_books();
    void handle_search_books();
    void handle_view_history();
    void handle_checkout_queue();
    void handle_search_by_id();
    void handle_borrow_book();
    void handle_return_book();
    void seed_sample_books();
    bool find_book_by_isbn(long long isbn, Book& out) const;
    bool remove_book_by_isbn(long long isbn, Book& removed);
    bool set_book_status(long long isbn, BookStatus new_status, std::string& message);

    ds::BinarySearchTree<Book> library_;
    ds::Stack<Book> recently_viewed_;
    ds::Queue<Book> checkout_queue_;
    ds::LinkedList<Book> wishlist_;
    ds::HashTable<long long> isbn_db_;
};
