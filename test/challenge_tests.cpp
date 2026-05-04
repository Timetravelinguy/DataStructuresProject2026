#include <algorithm>
#include <iostream>
#include <vector>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/hash_table.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/stack.hpp"
#include "library.hpp"

namespace {

void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << "\n";
        std::exit(1);
    }
}

}  // namespace

int main() {
    {
        ds::Stack<int> stack;
        stack.push(1);
        stack.push(2);
        stack.push(3);
        expect(stack.contains(2), "Stack contains existing value");
        expect(stack.index_of(3) == 2, "Stack index_of should return bottom-based index");
        stack.reverse();
        expect(stack.top() == 1, "Stack reverse should invert order");
    }

    {
        ds::Queue<int> queue;
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(1);
        expect(queue.is_palindrome(), "Queue palindrome check");
        queue.rotate(1);
        expect(queue.front() == 2, "Queue rotate should move front to back");
    }

    {
        ds::LinkedList<int> list;
        list.push_front(2);
        list.push_back(3);
        list.push_front(1);
        std::vector<int> expected{1, 2, 3};
        expect(list.to_vector() == expected, "LinkedList to_vector order");
        expect(list.erase_first(2), "LinkedList should erase existing value");
        expect(!list.erase_first(99), "LinkedList should return false when value missing");
    }

    {
        ds::HashTable<int> table;
        table.insert(10);
        table.insert(18);
        expect(table.contains(10), "HashTable contains inserted value");
        expect(table.contains(18), "HashTable should handle collisions");
        expect(table.erase(10), "HashTable erase existing value");
        expect(!table.contains(10), "HashTable should no longer contain erased value");
    }

    {
        ds::BinarySearchTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(6);
        std::vector<int> expected{3, 5, 6, 7};
        expect(tree.inorder() == expected, "BST inorder should be sorted");
        expect(tree.height() == 3, "BST height should match longest root-leaf path");
        expect(tree.remove(7), "BST remove existing node");
        expect(!tree.contains(7), "BST should not contain removed value");
    }

    {
        LibraryManager manager;
        Book found;
        std::string message;

        expect(manager.search_by_id(1001, found), "Search should find a preloaded book");
        expect(!manager.search_by_id(999999, found), "Search should fail for unknown ID");

        Book new_book(5001, "Project C++", "Team Three", 2026, "Technology", BookStatus::Available);
        expect(manager.add_book(new_book, message), "Adding a new valid book should succeed");
        expect(manager.search_by_id(5001, found), "Added book should be searchable by ID");

        const auto title_matches = manager.search_by_title_or_category("Project C++");
        expect(!title_matches.empty(), "Search by title should find added book");
        const auto category_matches = manager.search_by_title_or_category("Technology");
        expect(std::any_of(category_matches.begin(), category_matches.end(), [](const Book& b) { return b.isbn == 5001; }),
               "Search by category should find added book");

        expect(manager.borrow_book(5001, message), "Borrowing an available book should succeed");
        expect(!manager.borrow_book(5001, message), "Borrowing an already borrowed book should fail");

        expect(manager.return_book(5001, message), "Returning a borrowed book should succeed");
        expect(!manager.return_book(5001, message), "Returning an available book should fail");

        Book removed;
        expect(manager.remove_book(5001, removed), "Removing a valid book ID should succeed");
        expect(!manager.remove_book(5001, removed), "Removing an invalid book ID should fail");
    }

    std::cout << "challenge_tests.cpp passed.\n";
    return 0;
}
