#include <iostream>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/stack.hpp"

int main() {
    std::cout << "Data Structures Project 2026 shell is ready.\n";
    std::cout << "See docs/team_work_split.md for the 3-person challenge plan.\n";
    std::cout << "This shell is separate from src/book_manager/main.cpp, which builds the book manager CLI.\n";
    std::cout << "Implement the challenge methods inside include/datastructures/*.hpp.\n";

    // Placeholder usage to verify headers/sources are wired into the build.
    ds::Stack<int> stack;
    ds::Queue<int> queue;
    ds::LinkedList<int> list;
    ds::BinarySearchTree<int> tree;

    (void)stack;
    (void)queue;
    (void)list;
    (void)tree;

    return 0;
}