#include <iostream>
#include <vector>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/hash_table.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/stack.hpp"

namespace {

void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << "\n";
        std::exit(1);
    }
}

}  // namespace

int main() {
    // NOTE: This file is intentionally a guided checklist.
    // Uncomment each section after implementing its TODO methods.

    // Person 1 checks (Stack + Queue):
    // {
    //     ds::Stack<int> stack;
    //     stack.push(1);
    //     stack.push(2);
    //     stack.push(3);
    //     expect(stack.contains(2), "Stack contains existing value");
    //     expect(stack.index_of(3) == 2, "Stack index_of should return bottom-based index");
    //     stack.reverse();
    //     expect(stack.top() == 1, "Stack reverse should invert order");
    //
    //     ds::Queue<int> queue;
    //     queue.enqueue(1);
    //     queue.enqueue(2);
    //     queue.enqueue(1);
    //     expect(queue.is_palindrome(), "Queue palindrome check");
    //     queue.rotate(1);
    //     expect(queue.front() == 2, "Queue rotate should move front to back");
    // }

    // Person 2 checks (LinkedList):
    // {
    //     ds::LinkedList<int> list;
    //     list.push_front(2);
    //     list.push_back(3);
    //     list.push_front(1);
    //
    //     std::vector<int> expected{1, 2, 3};
    //     expect(list.to_vector() == expected, "LinkedList to_vector order");
    //     expect(list.erase_first(2), "LinkedList should erase existing value");
    //     expect(!list.erase_first(99), "LinkedList should return false when value missing");
    // }

    // Person 2 hash table checks:
    // {
    //     ds::HashTable<int> table;
    //     table.insert(10);
    //     table.insert(18); // likely collision if bucket count is small
    //     expect(table.contains(10), "HashTable contains inserted value");
    //     expect(table.contains(18), "HashTable should handle collisions");
    //     expect(table.erase(10), "HashTable erase existing value");
    //     expect(!table.contains(10), "HashTable should no longer contain erased value");
    // }

    // Person 3 checks (BinarySearchTree):
    // {
    //     ds::BinarySearchTree<int> tree;
    //     tree.insert(5);
    //     tree.insert(3);
    //     tree.insert(7);
    //     tree.insert(6);
    //
    //     std::vector<int> expected{3, 5, 6, 7};
    //     expect(tree.inorder() == expected, "BST inorder should be sorted");
    //     expect(tree.height() == 3, "BST height should match longest root-leaf path");
    //     expect(tree.remove(7), "BST remove existing node");
    //     expect(!tree.contains(7), "BST should not contain removed value");
    // }

    std::cout << "challenge_tests.cpp scaffold ready.\n";
    return 0;
}
