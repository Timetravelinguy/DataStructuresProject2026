# 3-Person Work Split (About 1 Hour Each)

Goal: each person gets a similar amount of coding + debugging work, with clear interfaces already provided.

## Person 1: Stack + Queue

Files:
- `include/datastructures/stack.hpp`
- `include/datastructures/queue.hpp`

Tasks:
1. Implement `Stack::contains`, `Stack::index_of`, and `Stack::reverse`.
2. Implement `Queue::rotate` and `Queue::is_palindrome`.
3. Add at least 5 tests for edge cases in `test/challenge_tests.cpp`.

Suggested edge cases:
- Empty stack/queue behavior.
- `rotate(0)`, `rotate(size)`, `rotate(size + 1)`.
- Palindrome true/false with odd and even sizes.

## Person 2: Linked List

Files:
- `include/datastructures/linked_list.hpp`

Tasks:
1. Implement `LinkedList::push_back`.
2. Implement `LinkedList::erase_first`.
3. Implement `LinkedList::to_vector`.
4. Add at least 5 tests in `test/challenge_tests.cpp`.

Suggested edge cases:
- Erase from empty list.
- Erase head, middle, and missing value.
- `to_vector` on empty and multi-node lists.

## Person 3: Binary Search Tree

Files:
- `include/datastructures/binary_search_tree.hpp`

Tasks:
1. Implement `BinarySearchTree::inorder`.
2. Implement `BinarySearchTree::height`.
3. Implement `BinarySearchTree::remove`.
4. Add at least 5 tests in `test/challenge_tests.cpp`.

Suggested edge cases:
- Remove leaf node.
- Remove node with one child.
- Remove node with two children.
- Height of empty vs non-empty trees.

## Team Definition of Done

1. All TODO methods are implemented.
2. `ctest --test-dir build -C Debug --output-on-failure` passes.
3. `test/challenge_tests.cpp` has meaningful edge-case coverage.
4. Every person can explain one tradeoff they made (simplicity vs performance, iterative vs recursive, etc.).
