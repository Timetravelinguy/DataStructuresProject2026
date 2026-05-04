#include <iostream>
#include <vector>
#include "include/datastructures/linked_list.hpp"
#include "include/datastructures/hash_table.hpp"
#include "include/datastructures/binary_search_tree.hpp"

template<typename T>
void print_vec(const std::vector<T>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    std::cout << "]\n";
}

int main() {
    // Demo 1 — LinkedList: push_front, push_back, erase_first -> [1,3]
    ds::LinkedList<int> ll;
    ll.push_back(1);
    ll.push_back(2);
    ll.push_back(3);
    ll.erase_first(2);
    std::cout << "LinkedList to_vector(): ";
    print_vec(ll.to_vector());

    // Demo 2 — HashTable: insert and contains (chaining)
    ds::HashTable<int> ht(8);
    ht.insert(10);
    ht.insert(18); // likely collides with 10 for some hashes
    ht.insert(26);
    std::cout << "HashTable contains 18: " << (ht.contains(18) ? "true" : "false") << "\n";

    // Demo 3 — BST remove with two children
    ds::BinarySearchTree<int> bst;
    // build tree where node 5 has two children 3 and 7
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    std::cout << "BST inorder before remove(5): ";
    print_vec(bst.inorder());
    bool removed = bst.remove(5);
    std::cout << "removed 5: " << (removed ? "true" : "false") << "\n";
    std::cout << "BST inorder after remove(5): ";
    print_vec(bst.inorder());

    return 0;
}