#include "library.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#ifdef _WIN32
#include <conio.h>
#include <io.h>
#endif

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
    std::cout << "  [" << book.isbn << "] \"" << book.title << "\" by " << book.author
              << " (" << book.year << ")"
              << " | Category: " << book.category
              << " | Status: " << status_to_text(book.status) << "\n";
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
#ifdef _WIN32
    const bool interactive_console = _isatty(_fileno(stdin));

    if (!interactive_console) {
        while (true) {
            std::string id_text = read_non_empty_line("\nEnter Book ID (13 digits): ");
            if (id_text.size() != 13 || id_text.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "[ERR] Book ID must be exactly 13 digits. Try again.\n";
                continue;
            }

            long long id = 0;
            if (parse_long_long(id_text, id) && id >= 1000000000000LL && id <= 9999999999999LL) {
                return id;
            }

            std::cout << "[ERR] Book ID must fit in the valid 13-digit range. Try again.\n";
        }
    }

    auto render_id_line = [](const std::string& digits, bool ready_to_submit) {
        std::cout << "\rEnter Book ID (13 digits): ";
        std::cout << digits;
        std::cout << std::string(13 - digits.size(), ' ');
        std::cout << " [" << digits.size() << "/13]";
        if (ready_to_submit) {
            std::cout << " Press Enter to confirm";
        }
        std::cout << std::flush;
    };

    while (true) {
        std::string digits;
        std::cout << '\n';
        render_id_line(digits, false);

        while (true) {
            int ch = _getch();

            if (ch == 27) {
                std::cout << "\n";
                throw OperationCancelled();
            }

            if (ch == '\r' || ch == '\n') {
                if (digits.size() == 13) {
                    break;
                }
                continue;
            }

            if (ch == 8) {
                if (!digits.empty()) {
                    digits.pop_back();
                    render_id_line(digits, digits.size() == 13);
                }
                continue;
            }

            if (std::isdigit(static_cast<unsigned char>(ch)) && digits.size() < 13) {
                digits.push_back(static_cast<char>(ch));
                render_id_line(digits, digits.size() == 13);
            }
        }

        std::cout << '\n';

        long long id = 0;
        if (parse_long_long(digits, id) && id >= 1000000000000LL && id <= 9999999999999LL) {
            return id;
        }

        std::cout << "[ERR] Book ID must fit in the valid 13-digit range. Try again.\n";
    }
#else
    while (true) {
        std::string id_text = read_non_empty_line("\nEnter Book ID (13 digits): ");
        if (id_text.size() != 13 || id_text.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "[ERR] Book ID must be exactly 13 digits. Try again.\n";
            continue;
        }

        long long id = 0;
        if (parse_long_long(id_text, id) && id >= 1000000000000LL && id <= 9999999999999LL) {
            return id;
        }

        std::cout << "[ERR] Book ID must fit in the valid 13-digit range. Try again.\n";
    }
#endif
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
        copy.pop_front_for_copy();
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

void Book::display() const {
    print_book_record(*this);
}

LibraryManager::LibraryManager() : storage_ready_(false) {
    load_or_seed_storage();
}

void LibraryManager::init_sample() {
    load_or_seed_storage();
}

std::string LibraryManager::to_lower(const std::string& s) {
    return lower_copy(s);
}

void LibraryManager::seed_sample_books() {
    const std::vector<Book> sample_books = {
        {9780000000001LL, "To Kill a Mockingbird", "Harper Lee", 1960, "Classic Literature", BookStatus::Available},
        {9780000000002LL, "1984", "George Orwell", 1949, "Dystopian Fiction", BookStatus::Available},
        {9780000000003LL, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "Classic Literature", BookStatus::Available},
        {9780000000004LL, "Pride and Prejudice", "Jane Austen", 1813, "Romance", BookStatus::Available},
        {9780000000005LL, "Jane Eyre", "Charlotte Bronte", 1847, "Classic Literature", BookStatus::Available},
        {9780000000006LL, "Brave New World", "Aldous Huxley", 1932, "Dystopian Fiction", BookStatus::Available},
        {9780000000007LL, "The Catcher in the Rye", "J. D. Salinger", 1951, "Coming of Age", BookStatus::Available},
        {9780000000008LL, "The Hobbit", "J. R. R. Tolkien", 1937, "Fantasy", BookStatus::Available},
        {9780000000009LL, "Fahrenheit 451", "Ray Bradbury", 1953, "Dystopian Fiction", BookStatus::Available},
        {9780000000010LL, "Moby-Dick", "Herman Melville", 1851, "Adventure", BookStatus::Available},
        {9780000000011LL, "The Odyssey", "Homer", 800, "Epic Poetry", BookStatus::Available},
        {9780000000012LL, "War and Peace", "Leo Tolstoy", 1869, "Historical Fiction", BookStatus::Available},
        {9780000000013LL, "Crime and Punishment", "Fyodor Dostoevsky", 1866, "Psychological Fiction", BookStatus::Available},
        {9780000000014LL, "The Lord of the Rings", "J. R. R. Tolkien", 1954, "Fantasy", BookStatus::Available},
        {9780000000015LL, "The Alchemist", "Paulo Coelho", 1988, "Philosophical Fiction", BookStatus::Available},
        {9780000000016LL, "The Chronicles of Narnia", "C. S. Lewis", 1950, "Fantasy", BookStatus::Available},
        {9780000000017LL, "Frankenstein", "Mary Shelley", 1818, "Horror", BookStatus::Available},
        {9780000000018LL, "Dracula", "Bram Stoker", 1897, "Horror", BookStatus::Available},
        {9780000000019LL, "Wuthering Heights", "Emily Bronte", 1847, "Gothic Fiction", BookStatus::Available},
        {9780000000020LL, "Little Women", "Louisa May Alcott", 1868, "Classic Literature", BookStatus::Available},
        {9780000000021LL, "The Kite Runner", "Khaled Hosseini", 2003, "Contemporary Fiction", BookStatus::Available},
        {9780000000022LL, "The Book Thief", "Markus Zusak", 2005, "Historical Fiction", BookStatus::Available},
        {9780000000023LL, "Sapiens", "Yuval Noah Harari", 2011, "History", BookStatus::Available},
        {9780000000024LL, "Atomic Habits", "James Clear", 2018, "Self-Help", BookStatus::Available},
        {9780000000025LL, "Educated", "Tara Westover", 2018, "Memoir", BookStatus::Available},
        {9780000000026LL, "The Silent Patient", "Alex Michaelides", 2019, "Thriller", BookStatus::Available},
        {9780000000027LL, "The Martian", "Andy Weir", 2011, "Science Fiction", BookStatus::Available},
        {9780000000028LL, "Dune", "Frank Herbert", 1965, "Science Fiction", BookStatus::Available},
        {9780000000029LL, "Where the Crawdads Sing", "Delia Owens", 2018, "Mystery", BookStatus::Available},
        {9780000000030LL, "The Name of the Wind", "Patrick Rothfuss", 2007, "Fantasy", BookStatus::Available},
    };

    for (const auto& book : sample_books) {
        library_.insert(book);
        isbn_db_.insert(book.isbn);
    }
}

void LibraryManager::load_or_seed_storage() {
    if (storage_ready_) {
        return;
    }

    const bool loaded_from_disk = load_from_disk();
    if (!loaded_from_disk || library_.inorder().size() < 30) {
        seed_sample_books();
        save_to_disk();
    }

    load_queue_from_disk();

    storage_ready_ = true;
}

bool LibraryManager::load_queue_from_disk() {
    std::ifstream input("queue.db");
    if (!input.is_open()) {
        return false;
    }

    long long isbn = 0;
    bool any = false;
    while (input >> isbn) {
        Book book;
        if (find_book_by_isbn(isbn, book)) {
            checkout_queue_.enqueue(book);
            any = true;
        }
    }

    return any || input.eof();
}

void LibraryManager::save_queue_to_disk() const {
    std::ofstream output("queue.db", std::ios::trunc);
    if (!output.is_open()) {
        return;
    }

    ds::Queue<Book> copy = checkout_queue_;
    while (!copy.empty()) {
        output << copy.front().isbn << '\n';
        copy.pop_front_for_copy();
    }
}

void LibraryManager::print_help() const {
    std::cout << "\n=== HELP: Menu Item Explanations ===\n";
    std::cout << "1: Add book - prompts for Book ID, title, author, year, and category, then saves it.\n";
    std::cout << "2: Remove book - removes a book by Book ID and saves the updated collection.\n";
    std::cout << "3: View all books - lists the full library sorted by year.\n";
    std::cout << "4: Search - case-insensitive substring match on title, author, or category.\n";
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

bool LibraryManager::load_from_disk() {
    std::ifstream input("books.db");
    if (!input.is_open()) {
        return false;
    }

    std::string line;
    bool any_books = false;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream line_stream(line);
        Book loaded_book;
        int status_value = 0;

        if (!(line_stream >> loaded_book.isbn
                         >> std::quoted(loaded_book.title)
                         >> std::quoted(loaded_book.author)
                         >> loaded_book.year)) {
            continue;
        }

        loaded_book.category = "General";
        loaded_book.status = BookStatus::Available;

        if (line_stream >> std::quoted(loaded_book.category)) {
            if (line_stream >> status_value) {
                loaded_book.status = status_value == 0 ? BookStatus::Available : BookStatus::Borrowed;
            }
        }

        library_.insert(loaded_book);
        isbn_db_.insert(loaded_book.isbn);
        any_books = true;
    }

    return any_books;
}

void LibraryManager::save_to_disk() const {
    std::ofstream output("books.db", std::ios::trunc);
    if (!output.is_open()) {
        return;
    }

    for (const auto& book : library_.inorder()) {
        output << book.isbn << ' '
               << std::quoted(book.title) << ' '
               << std::quoted(book.author) << ' '
               << book.year << ' '
               << std::quoted(book.category) << ' '
               << (book.status == BookStatus::Borrowed ? 1 : 0) << '\n';
    }
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

    ds::Queue<Book> filtered_queue;
    ds::Queue<Book> queue_copy = checkout_queue_;
    while (!queue_copy.empty()) {
        if (queue_copy.front().isbn != isbn) {
            filtered_queue.enqueue(queue_copy.front());
        }
        queue_copy.pop_front_for_copy();
    }
    checkout_queue_ = filtered_queue;
    save_queue_to_disk();

    save_to_disk();
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
    save_to_disk();
    message = new_status == BookStatus::Borrowed ? "Book borrowed successfully." : "Book returned successfully.";
    return true;
}

void LibraryManager::print_menu() const {
    std::cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Add book to collection\n";
    std::cout << "2. Remove book from collection\n";
    std::cout << "3. View all books (sorted by year)\n";
    std::cout << "4. Search for a book by title, author, or category\n";
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
                long long isbn = read_book_id();
                if (isbn_db_.contains(isbn)) {
                    std::cout << "\n[ERR] A book with that ID already exists.\n";
                    continue;
                }

                std::string title = read_non_empty_line("Enter book title: ");
                std::string author = read_non_empty_line("Enter author: ");
                int year = read_publication_year();
                std::string category = read_non_empty_line("Enter category: ");

                Book new_book(isbn, title, author, year, category, BookStatus::Available);
                library_.insert(new_book);
                isbn_db_.insert(isbn);
                save_to_disk();
                std::cout << "\n[OK] Book added successfully!\n";
            } else if (choice == "2") {
                long long isbn = read_book_id();
                Book removed_book;
                if (remove_book_by_isbn(isbn, removed_book)) {
                    std::cout << "\n[OK] Removed book: ";
                    removed_book.display();
                } else {
                    std::cout << "\n[ERR] Book ID not found.\n";
                }
            } else if (choice == "3") {
                auto all_books = library_.inorder();
                if (all_books.empty()) {
                    std::cout << "\nLibrary is empty.\n";
                } else {
                    std::cout << "\n=== LIBRARY COLLECTION (sorted by year) ===\n";
                    for (const auto& book : all_books) {
                        book.display();
                    }
                    std::cout << "Total books: " << all_books.size() << "\n";
                }
            } else if (choice == "4") {
                std::string query = read_non_empty_line("\nEnter title, author, or category to search: ");
                auto all_books = library_.inorder();
                std::vector<Book> matches;

                for (const auto& book : all_books) {
                    if (contains_case_insensitive(book.title, query) ||
                        contains_case_insensitive(book.author, query) ||
                        contains_case_insensitive(book.category, query)) {
                        matches.push_back(book);
                    }
                }

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
            } else if (choice == "5") {
                std::cout << "\n=== RECENTLY VIEWED BOOKS ===\n";
                if (recently_viewed_.empty()) {
                    std::cout << "No books viewed yet.\n";
                } else {
                    ds::Stack<Book> temp = recently_viewed_;
                    if (temp.size() > 0) {
                        std::cout << "  Top (most recent): " << temp.top().title << " by " << temp.top().author << "\n";
                    }
                    std::cout << "Total books in view history: " << temp.size() << "\n";
                }
            } else if (choice == "6") {
                std::cout << "\n=== CHECKOUT QUEUE ===\n";
                print_queue_snapshot(checkout_queue_);

                std::cout << "\n1. Add a book to the queue\n";
                std::cout << "2. Remove the front book from the queue\n";
                std::cout << "3. Return to main menu\n";
                std::cout << "Choose an action: ";

                std::string queue_choice;
                if (!std::getline(std::cin, queue_choice)) {
                    continue;
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
                                save_queue_to_disk();
                                std::cout << "\n[OK] Added to checkout queue: ";
                                selected.display();
                            }
                        }
                    }
                } else if (queue_choice == "2") {
                    if (checkout_queue_.empty()) {
                        std::cout << "[ERR] Queue is already empty.\n";
                    } else {
                        std::cout << "Removing: ";
                        checkout_queue_.front().display();
                        checkout_queue_.dequeue();
                        save_queue_to_disk();
                        std::cout << "[OK] Removed front book from the queue.\n";
                    }
                }
            } else if (choice == "7") {
                long long isbn = read_book_id();
                Book found_book;
                if (find_book_by_isbn(isbn, found_book)) {
                    std::cout << "\n[OK] Book found:\n";
                    found_book.display();
                    recently_viewed_.push(found_book);
                    std::cout << "Added to recently viewed.\n";
                } else {
                    std::cout << "\n[ERR] Book ID not found.\n";
                }
            } else if (choice == "8") {
                long long isbn = read_book_id();
                std::string message;
                if (set_book_status(isbn, BookStatus::Borrowed, message)) {
                    std::cout << "\n[OK] " << message << "\n";
                } else {
                    std::cout << "\n[ERR] " << message << "\n";
                }
            } else if (choice == "9") {
                long long isbn = read_book_id();
                std::string message;
                if (set_book_status(isbn, BookStatus::Available, message)) {
                    std::cout << "\n[OK] " << message << "\n";
                } else {
                    std::cout << "\n[ERR] " << message << "\n";
                }
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

