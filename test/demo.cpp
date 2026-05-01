#include <iostream>
#include <string>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/hash_table.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/stack.hpp"

int main() {
    std::cout << "\n=== DATA STRUCTURES PROJECT 2026 - USER DEMO ===\n\n";

    // ========== STACK DEMO ==========
    std::cout << "--- STACK DEMO ---\n";
    std::cout << "A stack is like a stack of plates: last in, first out.\n";
    ds::Stack<int> history;
    history.push(100);
    history.push(200);
    history.push(300);
    std::cout << "Pushed: 100, 200, 300\n";
    std::cout << "Top item: " << history.top() << "\n";
    std::cout << "Contains 200? " << (history.contains(200) ? "Yes" : "No") << "\n";
    std::cout << "Index of 200 (from bottom): " << history.index_of(200) << "\n";
    history.reverse();
    std::cout << "After reversing, top item: " << history.top() << "\n\n";

    // ========== QUEUE DEMO ==========
    std::cout << "--- QUEUE DEMO ---\n";
    std::cout << "A queue is like a line: first in, first out.\n";
    ds::Queue<int> line;
    line.enqueue(1);
    line.enqueue(2);
    line.enqueue(1);
    std::cout << "Enqueued: 1, 2, 1\n";
    std::cout << "Front of line: " << line.front() << "\n";
    std::cout << "Is palindrome (1-2-1)? " << (line.is_palindrome() ? "Yes" : "No") << "\n";
    line.rotate(1);
    std::cout << "After rotating by 1, front: " << line.front() << "\n\n";

    // ========== LINKED LIST DEMO ==========
    std::cout << "--- LINKED LIST DEMO ---\n";
    std::cout << "A linked list chains items together.\n";
    ds::LinkedList<std::string> items;
    items.push_front("Apple");
    items.push_back("Banana");
    items.push_back("Cherry");
    std::cout << "Built list: Apple -> Banana -> Cherry\n";
    auto vec = items.to_vector();
    std::cout << "Items in order: ";
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    bool removed = items.erase_first("Banana");
    std::cout << "Removed 'Banana'? " << (removed ? "Yes" : "No") << "\n";
    vec = items.to_vector();
    std::cout << "After removal: ";
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n\n";

    // ========== HASH TABLE DEMO ==========
    std::cout << "--- HASH TABLE DEMO ---\n";
    std::cout << "A hash table stores unique values for fast lookup.\n";
    ds::HashTable<int> memberSet;
    memberSet.insert(42);
    memberSet.insert(17);
    memberSet.insert(99);
    std::cout << "Inserted: 42, 17, 99\n";
    std::cout << "Contains 42? " << (memberSet.contains(42) ? "Yes" : "No") << "\n";
    std::cout << "Contains 50? " << (memberSet.contains(50) ? "Yes" : "No") << "\n";
    std::cout << "Bucket count: " << memberSet.bucket_count() << "\n";
    memberSet.erase(17);
    std::cout << "After erasing 17, contains 17? " << (memberSet.contains(17) ? "Yes" : "No") << "\n\n";

    // ========== BINARY SEARCH TREE DEMO ==========
    std::cout << "--- BINARY SEARCH TREE DEMO ---\n";
    std::cout << "A BST keeps values sorted for fast search and range queries.\n";
    ds::BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    std::cout << "Inserted: 50, 30, 70, 20, 40, 60, 80\n";
    
    auto sorted = tree.inorder();
    std::cout << "In-order traversal (sorted): ";
    for (int val : sorted) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "Tree height: " << tree.height() << "\n";
    std::cout << "Contains 40? " << (tree.contains(40) ? "Yes" : "No") << "\n";
    
    tree.remove(30);
    std::cout << "After removing 30, in-order: ";
    sorted = tree.inorder();
    for (int val : sorted) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "Contains 30? " << (tree.contains(30) ? "Yes" : "No") << "\n\n";

    std::cout << "=== END DEMO ===\n";
    return 0;
}
