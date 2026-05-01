#include "library.hpp"

#include <iostream>
#include <algorithm>

void Book::display() const {
    std::cout << "  \"" << title << "\" by " << author << " (" << year << ")\n";
}

LibraryManager::LibraryManager() {}

void LibraryManager::init_sample() {
    Book b1("To Kill a Mockingbird", "Harper Lee", 1960);
    Book b2("1984", "George Orwell", 1949);
    Book b3("The Great Gatsby", "F. Scott Fitzgerald", 1925);
    Book b4("Jane Eyre", "Charlotte Bronte", 1847);
    Book b5("Pride and Prejudice", "Jane Austen", 1813);

    library_.insert(b1);
    library_.insert(b2);
    library_.insert(b3);
    library_.insert(b4);
    library_.insert(b5);

    isbn_db_.insert(9780061120084);
    isbn_db_.insert(9780451524935);
    isbn_db_.insert(9780743273565);
    isbn_db_.insert(9780142437209);
    isbn_db_.insert(9780141439518);
}

std::string LibraryManager::to_lower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

void LibraryManager::print_menu() const {
    std::cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Add book to collection\n";
    std::cout << "2. Remove book from collection\n";
    std::cout << "3. View all books (sorted by year)\n";
    std::cout << "4. Search for a book\n";
    std::cout << "5. View recently viewed books\n";
    std::cout << "6. View checkout queue\n";
    std::cout << "7. Check if ISBN exists\n";
    std::cout << "8. Display menu\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}

void LibraryManager::run_cli() {
    std::cout << "\nLibrary Manager starting...\n";
    bool running = true;
    while (running) {
        print_menu();
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string title, author, year_str;
            std::cout << "\nEnter book title: ";
            std::getline(std::cin, title);
            std::cout << "Enter author: ";
            std::getline(std::cin, author);
            std::cout << "Enter publication year: ";
            std::getline(std::cin, year_str);
            try {
                int year = std::stoi(year_str);
                Book new_book(title, author, year);
                library_.insert(new_book);
                int isbn = 9780000000000 + (isbn_db_.size() * 100);
                isbn_db_.insert(isbn);
                std::cout << "\n✓ Book added successfully!\n";
            } catch (...) { std::cout << "\n✗ Invalid input.\n"; }

        } else if (choice == "2") {
            std::string title;
            std::cout << "\nEnter book title to remove: ";
            std::getline(std::cin, title);
            auto all_books = library_.inorder();
            Book to_remove; bool found = false;
            for (const auto& book : all_books) {
                if (to_lower(book.title) == to_lower(title)) { to_remove = book; found = true; break; }
            }
            if (found) { library_.remove(to_remove); std::cout << "\n✓ Book removed.\n"; }
            else { std::cout << "\n✗ Not found.\n"; }

        } else if (choice == "3") {
            auto all_books = library_.inorder();
            if (all_books.empty()) { std::cout << "\nLibrary is empty.\n"; }
            else {
                std::cout << "\n=== LIBRARY COLLECTION (sorted by year) ===\n";
                for (const auto& book : all_books) book.display();
                std::cout << "Total books: " << all_books.size() << "\n";
            }

        } else if (choice == "4") {
            std::string title; std::cout << "\nEnter book title to search: "; std::getline(std::cin, title);
            auto all_books = library_.inorder(); Book found_book; bool found=false;
            for (const auto& book: all_books) { if (to_lower(book.title)==to_lower(title)) { found_book=book; found=true; break; } }
            if (found) { std::cout<<"\n✓ Book found:\n"; found_book.display(); recently_viewed_.push(found_book); std::cout<<"Added to recently viewed.\n"; }
            else { std::cout<<"\n✗ Book not found.\n"; }

        } else if (choice == "5") {
            std::cout << "\n=== RECENTLY VIEWED BOOKS ===\n";
            if (recently_viewed_.empty()) { std::cout<<"No books viewed yet.\n"; }
            else { ds::Stack<Book> temp = recently_viewed_; if (temp.size()>0) { std::cout<<"  Top (most recent): "<<temp.top().title<<" by "<<temp.top().author<<"\n"; } std::cout<<"Total books in view history: "<<temp.size()<<"\n"; }

        } else if (choice == "6") {
            std::cout << "\n=== CHECKOUT QUEUE ===\n";
            if (checkout_queue_.empty()) {
                std::cout << "Queue is empty.\n";
                std::cout << "Add a book to queue? Enter title (or 'skip'): ";
                std::string title; std::getline(std::cin, title);
                if (title!="skip") { auto all_books=library_.inorder(); for (auto &b: all_books) if (to_lower(b.title)==to_lower(title)) { checkout_queue_.enqueue(b); std::cout<<"\n✓ Added to checkout queue.\n"; break; } }
            } else {
                std::cout<<"Next in queue: "; checkout_queue_.front().display(); std::cout<<"Remove from queue? (y/n): "; std::string resp; std::getline(std::cin,resp); if (resp=="y"||resp=="yes") { checkout_queue_.dequeue(); std::cout<<"✓ Removed.\n"; }
            }

        } else if (choice == "7") {
            std::cout<<"\nEnter ISBN to check: "; std::string isbn_str; std::getline(std::cin,isbn_str);
            try { int isbn=std::stoi(isbn_str); bool exists=isbn_db_.contains(isbn); std::cout<<(exists?"✓ ISBN exists.\n":"✗ ISBN not found.\n"); } catch(...) { std::cout<<"✗ Invalid ISBN.\n"; }

        } else if (choice == "8") { continue; }
        else if (choice == "9") { running=false; std::cout<<"\nGoodbye!\n"; }
        else { std::cout<<"\n✗ Invalid choice.\n"; }
    }
}

