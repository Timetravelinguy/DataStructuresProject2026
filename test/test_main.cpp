#include <iostream>

#include "datastructures/binary_search_tree.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/stack.hpp"

int main() {
    ds::Stack<int> stack;
    stack.push(5);

    ds::Queue<int> queue;
    queue.enqueue(10);

    ds::BinarySearchTree<int> tree;
    tree.insert(42);

    if (stack.top() == 5 && queue.front() == 10 && tree.contains(42)) {
        std::cout << "Basic shell test passed.\n";
        return 0;
    }

    std::cerr << "Basic shell test failed.\n";
    return 1;
}
