#include "library.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

namespace {

struct OperationCancelled {};

std::string lower_copy(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

bool is_cancel_command(const std::string& value) {
    return lower_copy(value) == "cancel";
}

std::string status_to_text(BookStatus status) {
    return status == BookStatus::Borrowed ? "Borrowed" : "Available";
}

void print_book_record(const Book& book) {
    std::cout << "  " << book << "\n";
}

bool contains_case_insensitive(const std::string& haystack, const std::string& needle) {
    return lower_copy(haystack).find(lower_copy(needle)) != std::string::npos;
}

std::string read_non_empty_line(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            throw OperationCancelled();
        }

        if (is_cancel_command(value)) {
            throw OperationCancelled();
        }

        if (!value.empty()) {
            return value;
        }

        std::cout << "[ERR] This field cannot be empty. Try again.\n";
    }
}

bool parse_int(const std::string& text, int& value) {
    try {
        std::size_t parsed_chars = 0;
        int parsed = std::stoi(text, &parsed_chars);
        if (parsed_chars == text.size()) {
            value = parsed;
            return true;
        }
    } catch (...) {
    }
    return false;
}

bool parse_long_long(const std::string& text, long long& value) {
    try {
        std::size_t parsed_chars = 0;
        long long parsed = std::stoll(text, &parsed_chars);
        if (parsed_chars == text.size()) {
            value = parsed;
            return true;
        }
    } catch (...) {
    }
    return false;
}

long long read_book_id() {
    while (true) {
        std::string id_text = read_non_empty_line("\nEnter Book ID (positive integer): ");
        long long id = 0;
        if (parse_long_long(id_text, id) && id > 0) {
            return id;
        }

        std::cout << "[ERR] Book ID must be a positive integer. Try again.\n";
    }
}

int read_publication_year() {
    while (true) {
        std::string year_str = read_non_empty_line("Enter publication year: ");
        int year = 0;
        if (parse_int(year_str, year) && year > 0) {
            return year;
        }

        std::cout << "[ERR] Publication year must be a whole number. Try again.\n";
    }
}

void print_queue_snapshot(const ds::Queue<Book>& queue) {
    if (queue.empty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    ds::Queue<Book> copy = queue;
    std::size_t position = 1;
    while (!copy.empty()) {
        std::cout << position << ". ";
        print_book_record(copy.front());
        copy.dequeue();
        ++position;
    }
}

std::vector<Book> search_candidates_by_title(const std::vector<Book>& books, const std::string& query) {
    std::vector<Book> candidates;
    for (const auto& book : books) {
        if (contains_case_insensitive(book.title, query)) {
            candidates.push_back(book);
        }
    }
    return candidates;
}

void purge_wishlist_by_isbn(ds::LinkedList<Book>& wishlist, long long isbn) {
    const std::vector<Book> existing = wishlist.to_vector();
    for (const auto& item : existing) {
        wishlist.erase_first(item);
    }
    for (const auto& item : existing) {
        if (item.isbn != isbn) {
            wishlist.push_back(item);
        }
    }
}

bool prompt_candidate_selection(const std::vector<Book>& candidates, Book& selected) {
    if (candidates.empty()) {
        return false;
    }

    if (candidates.size() == 1) {
        selected = candidates.front();
        return true;
    }

    std::cout << "\nMultiple matches found:\n";
    for (std::size_t i = 0; i < candidates.size(); ++i) {
        std::cout << (i + 1) << ". ";
        print_book_record(candidates[i]);
    }

    while (true) {
        std::string selection = read_non_empty_line("Select number to enqueue (or type 'skip'): ");
        if (lower_copy(selection) == "skip") {
            return false;
        }

        int index = 0;
        if (parse_int(selection, index) && index >= 1 && index <= static_cast<int>(candidates.size())) {
            selected = candidates[static_cast<std::size_t>(index - 1)];
            return true;
        }

        std::cout << "[ERR] Invalid selection. Try again.\n";
    }
}

}  // namespace

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "[" << book.isbn << "] \"" << book.title << "\" by " << book.author
       << " (" << book.year << ")"
       << " | Category: " << book.category
       << " | Status: " << status_to_text(book.status);
    return os;
}

void Book::display() const {
    print_book_record(*this);
}

LibraryManager::LibraryManager() {
    seed_sample_books();
}

void LibraryManager::seed_sample_books() {
    const std::vector<Book> sample_books = {
        {1001, "To Kill a Mockingbird", "Harper Lee", 1960, "Classic Literature", BookStatus::Available},
        {1002, "1984", "George Orwell", 1949, "Dystopian Fiction", BookStatus::Available},
        {1003, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "Classic Literature", BookStatus::Available},
        {1004, "Pride and Prejudice", "Jane Austen", 1813, "Romance", BookStatus::Available},
        {1005, "Jane Eyre", "Charlotte Bronte", 1847, "Classic Literature", BookStatus::Available},
        {1006, "Brave New World", "Aldous Huxley", 1932, "Dystopian Fiction", BookStatus::Available},
        {1007, "The Catcher in the Rye", "J. D. Salinger", 1951, "Coming of Age", BookStatus::Available},
        {1008, "The Hobbit", "J. R. R. Tolkien", 1937, "Fantasy", BookStatus::Available},
        {1009, "Fahrenheit 451", "Ray Bradbury", 1953, "Dystopian Fiction", BookStatus::Available},
        {1010, "Moby-Dick", "Herman Melville", 1851, "Adventure", BookStatus::Available},
        {1011, "The Odyssey", "Homer", 800, "Epic Poetry", BookStatus::Available},
        {1012, "War and Peace", "Leo Tolstoy", 1869, "Historical Fiction", BookStatus::Available},
        {1013, "Crime and Punishment", "Fyodor Dostoevsky", 1866, "Psychological Fiction", BookStatus::Available},
        {1014, "The Lord of the Rings", "J. R. R. Tolkien", 1954, "Fantasy", BookStatus::Available},
        {1015, "The Alchemist", "Paulo Coelho", 1988, "Philosophical Fiction", BookStatus::Available},
        {1016, "The Chronicles of Narnia", "C. S. Lewis", 1950, "Fantasy", BookStatus::Available},
        {1017, "Frankenstein", "Mary Shelley", 1818, "Horror", BookStatus::Available},
        {1018, "Dracula", "Bram Stoker", 1897, "Horror", BookStatus::Available},
        {1019, "Wuthering Heights", "Emily Bronte", 1847, "Gothic Fiction", BookStatus::Available},
        {1020, "Little Women", "Louisa May Alcott", 1868, "Classic Literature", BookStatus::Available},
        {1021, "The Kite Runner", "Khaled Hosseini", 2003, "Contemporary Fiction", BookStatus::Available},
        {1022, "The Book Thief", "Markus Zusak", 2005, "Historical Fiction", BookStatus::Available},
        {1023, "Sapiens", "Yuval Noah Harari", 2011, "History", BookStatus::Available},
        {1024, "Atomic Habits", "James Clear", 2018, "Self-Help", BookStatus::Available},
        {1025, "Educated", "Tara Westover", 2018, "Memoir", BookStatus::Available},
        {1026, "The Silent Patient", "Alex Michaelides", 2019, "Thriller", BookStatus::Available},
        {1027, "The Martian", "Andy Weir", 2011, "Science Fiction", BookStatus::Available},
        {1028, "Dune", "Frank Herbert", 1965, "Science Fiction", BookStatus::Available},
        {1029, "Where the Crawdads Sing", "Delia Owens", 2018, "Mystery", BookStatus::Available},
        {1030, "The Name of the Wind", "Patrick Rothfuss", 2007, "Fantasy", BookStatus::Available},
    };

    for (const auto& book : sample_books) {
        library_.insert(book);
        isbn_db_.insert(book.isbn);
    }
}

bool LibraryManager::add_book(const Book& book, std::string& message) {
    if (book.isbn <= 0) {
        message = "Book ID must be a positive integer.";
        return false;
    }
    if (book.year <= 0) {
        message = "Publication year must be a whole number.";
        return false;
    }
    if (book.title.empty() || book.author.empty() || book.category.empty()) {
        message = "Title, author, and category are required.";
        return false;
    }
    if (isbn_db_.contains(book.isbn)) {
        message = "A book with that ID already exists.";
        return false;
    }

    library_.insert(book);
    isbn_db_.insert(book.isbn);
    message = "Book added successfully.";
    return true;
}

bool LibraryManager::remove_book(long long isbn, Book& removed) {
    return remove_book_by_isbn(isbn, removed);
}

bool LibraryManager::search_by_id(long long isbn, Book& out) const {
    return find_book_by_isbn(isbn, out);
}

std::vector<Book> LibraryManager::search_by_title_or_category(const std::string& query) const {
    std::vector<Book> matches;
    for (const auto& book : library_.inorder()) {
        if (contains_case_insensitive(book.title, query) ||
            contains_case_insensitive(book.category, query)) {
            matches.push_back(book);
        }
    }
    return matches;
}

std::vector<Book> LibraryManager::list_books() const {
    return library_.inorder();
}

bool LibraryManager::borrow_book(long long isbn, std::string& message) {
    return set_book_status(isbn, BookStatus::Borrowed, message);
}

bool LibraryManager::return_book(long long isbn, std::string& message) {
    return set_book_status(isbn, BookStatus::Available, message);
}

void LibraryManager::print_help() const {
    std::cout << "\n=== HELP: Menu Item Explanations ===\n";
    std::cout << "1: Add book - prompts for Book ID, title, author, year, and category.\n";
    std::cout << "2: Remove book - removes a book by Book ID from the collection.\n";
    std::cout << "3: View all books - lists the full library sorted by year.\n";
    std::cout << "4: Search - case-insensitive substring match on title or category.\n";
    std::cout << "5: Recently viewed - shows the most recent books you opened or searched.\n";
    std::cout << "6: Checkout queue - shows the queue and lets you add or remove books.\n";
    std::cout << "7: Search by Book ID - exact lookup by ID.\n";
    std::cout << "8: Borrow book - marks a book as Borrowed if it is currently available.\n";
    std::cout << "9: Return book - marks a book as Available if it is currently borrowed.\n";
    std::cout << "10: Display menu - reprints the main menu options.\n";
    std::cout << "11: Help - shows this help page.\n";
    std::cout << "12: Exit - quit the program.\n";
    std::cout << "Type 'cancel' during prompts to return to the menu.\n";
}



bool LibraryManager::find_book_by_isbn(long long isbn, Book& out) const {
    for (const auto& book : library_.inorder()) {
        if (book.isbn == isbn) {
            out = book;
            return true;
        }
    }
    return false;
}

bool LibraryManager::remove_book_by_isbn(long long isbn, Book& removed) {
    if (!find_book_by_isbn(isbn, removed)) {
        return false;
    }

    if (!library_.remove(removed)) {
        return false;
    }

    isbn_db_.erase(isbn);
    purge_wishlist_by_isbn(wishlist_, isbn);

    ds::Queue<Book> filtered_queue;
    ds::Queue<Book> queue_copy = checkout_queue_;
    while (!queue_copy.empty()) {
        if (queue_copy.front().isbn != isbn) {
            filtered_queue.enqueue(queue_copy.front());
        }
        queue_copy.dequeue();
    }
    checkout_queue_ = filtered_queue;

    return true;
}

bool LibraryManager::set_book_status(long long isbn, BookStatus new_status, std::string& message) {
    Book book;
    if (!find_book_by_isbn(isbn, book)) {
        message = "Book ID not found.";
        return false;
    }

    if (book.status == new_status) {
        message = new_status == BookStatus::Borrowed ? "That book is already borrowed." : "That book is already available.";
        return false;
    }

    if (!library_.remove(book)) {
        message = "Could not update the selected book.";
        return false;
    }

    book.status = new_status;
    library_.insert(book);
    message = new_status == BookStatus::Borrowed ? "Book borrowed successfully." : "Book returned successfully.";
    return true;
}

void LibraryManager::print_menu() const {
    std::cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Add book to collection\n";
    std::cout << "2. Remove book from collection\n";
    std::cout << "3. View all books (sorted by year)\n";
    std::cout << "4. Search for a book by title or category\n";
    std::cout << "5. View recently viewed books\n";
    std::cout << "6. View or edit checkout queue\n";
    std::cout << "7. Search for a book by Book ID\n";
    std::cout << "8. Borrow a book\n";
    std::cout << "9. Return a book\n";
    std::cout << "10. Display menu\n";
    std::cout << "11. Help (explain menu items)\n";
    std::cout << "12. Exit\n";
    std::cout << "Choose an option: ";
}

void LibraryManager::handle_add_book() {
    long long isbn = read_book_id();
    std::string title = read_non_empty_line("Enter book title: ");
    std::string author = read_non_empty_line("Enter author: ");
    int year = read_publication_year();
    std::string category = read_non_empty_line("Enter category: ");

    std::string message;
    Book new_book(isbn, title, author, year, category, BookStatus::Available);
    if (add_book(new_book, message)) {
        std::cout << "\n[OK] " << message << "\n";
    } else {
        std::cout << "\n[ERR] " << message << "\n";
    }
}

void LibraryManager::handle_remove_book() {
    long long isbn = read_book_id();
    Book removed_book;
    if (remove_book(isbn, removed_book)) {
        std::cout << "\n[OK] Removed book: ";
        removed_book.display();
    } else {
        std::cout << "\n[ERR] Book ID not found.\n";
    }
}

void LibraryManager::handle_view_books() {
    auto books = list_books();
    if (books.empty()) {
        std::cout << "\nLibrary is empty.\n";
    } else {
        std::cout << "\n=== LIBRARY COLLECTION (sorted by year) ===\n";
        for (const auto& book : books) {
            book.display();
        }
        std::cout << "Total books: " << books.size() << "\n";
    }
}

void LibraryManager::handle_search_books() {
    std::string query = read_non_empty_line("\nEnter title or category to search: ");
    std::vector<Book> matches = search_by_title_or_category(query);

    if (matches.empty()) {
        std::cout << "\n[ERR] No books matched that search.\n";
    } else {
        std::cout << "\n[OK] Found " << matches.size() << " match" << (matches.size() == 1 ? "" : "es") << ":\n";
        for (const auto& book : matches) {
            book.display();
            recently_viewed_.push(book);
        }
        std::cout << "Added matches to recently viewed.\n";
    }
}

void LibraryManager::handle_view_history() {
    std::cout << "\n=== RECENTLY VIEWED BOOKS ===\n";
    if (recently_viewed_.empty()) {
        std::cout << "No books viewed yet.\n";
        return;
    }

    ds::Stack<Book> temp = recently_viewed_;
    if (temp.size() > 0) {
        std::cout << "  Top (most recent): " << temp.top().title << " by " << temp.top().author << "\n";
    }
    std::cout << "Total books in view history: " << temp.size() << "\n";
}

void LibraryManager::handle_checkout_queue() {
    std::cout << "\n=== CHECKOUT QUEUE ===\n";
    print_queue_snapshot(checkout_queue_);

    std::cout << "\n1. Add a book to the queue\n";
    std::cout << "2. Remove the front book from the queue\n";
    std::cout << "3. Return to main menu\n";
    std::cout << "Choose an action: ";

    std::string queue_choice;
    if (!std::getline(std::cin, queue_choice)) {
        return;
    }

    if (queue_choice == "1") {
        std::string query = read_non_empty_line("Search title to add to queue (or type 'skip'): ");
        if (lower_copy(query) != "skip") {
            std::vector<Book> candidates = search_candidates_by_title(library_.inorder(), query);

            if (candidates.empty()) {
                std::cout << "\n[ERR] No matches found for '" << query << "'.\n";
            } else {
                Book selected;
                if (prompt_candidate_selection(candidates, selected)) {
                    checkout_queue_.enqueue(selected);
                    wishlist_.push_back(selected);
                    std::cout << "\n[OK] Added to checkout queue: ";
                    selected.display();
                }
            }
        }
    } else if (queue_choice == "2") {
        if (checkout_queue_.empty()) {
            std::cout << "[ERR] Queue is already empty.\n";
        } else {
            const Book removed_from_queue = checkout_queue_.front();
            std::cout << "Removing: ";
            removed_from_queue.display();
            checkout_queue_.dequeue();
            wishlist_.erase_first(removed_from_queue);
            std::cout << "[OK] Removed front book from the queue.\n";
        }
    }
}

void LibraryManager::handle_search_by_id() {
    long long isbn = read_book_id();
    Book found_book;
    if (search_by_id(isbn, found_book)) {
        std::cout << "\n[OK] Book found:\n";
        found_book.display();
        recently_viewed_.push(found_book);
        std::cout << "Added to recently viewed.\n";
    } else {
        std::cout << "\n[ERR] Book ID not found.\n";
    }
}

void LibraryManager::handle_borrow_book() {
    long long isbn = read_book_id();
    std::string message;
    if (borrow_book(isbn, message)) {
        std::cout << "\n[OK] " << message << "\n";
    } else {
        std::cout << "\n[ERR] " << message << "\n";
    }
}

void LibraryManager::handle_return_book() {
    long long isbn = read_book_id();
    std::string message;
    if (return_book(isbn, message)) {
        std::cout << "\n[OK] " << message << "\n";
    } else {
        std::cout << "\n[ERR] " << message << "\n";
    }
}

void LibraryManager::run_cli() {
    std::cout << "\nLibrary Manager starting...\n";
    bool running = true;

    while (running) {
        print_menu();

        std::string choice;
        if (!std::getline(std::cin, choice)) {
            break;
        }

        try {
            if (choice == "1") {
                handle_add_book();
            } else if (choice == "2") {
                handle_remove_book();
            } else if (choice == "3") {
                handle_view_books();
            } else if (choice == "4") {
                handle_search_books();
            } else if (choice == "5") {
                handle_view_history();
            } else if (choice == "6") {
                handle_checkout_queue();
            } else if (choice == "7") {
                handle_search_by_id();
            } else if (choice == "8") {
                handle_borrow_book();
            } else if (choice == "9") {
                handle_return_book();
            } else if (choice == "10") {
                continue;
            } else if (choice == "11") {
                print_help();
            } else if (choice == "12") {
                running = false;
                std::cout << "\nGoodbye!\n";
            } else {
                std::cout << "\n[ERR] Invalid choice.\n";
            }
        } catch (OperationCancelled&) {
            std::cout << "\n[OK] Operation cancelled. Returning to menu.\n";
        } catch (const std::exception&) {
            std::cout << "\n[ERR] Invalid input. Returning to menu.\n";
        }
    }
}

