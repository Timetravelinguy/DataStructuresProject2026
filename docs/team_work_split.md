# 3-Person Work Split (2 x 30 min, 1 x 90 min)

Goal: two people get a shorter, well-scoped 30-minute implementation task, while the experienced person gets the longer 90-minute challenge with deeper design and debugging work.

## Person 1: Stack + Queue 30 min

Files:
- `include/datastructures/stack.hpp`
- `include/datastructures/queue.hpp`

Tasks:
1. Implement `Stack::contains`, `Stack::index_of`, and `Stack::reverse`.
2. Implement `Queue::rotate` and `Queue::is_palindrome`.
3. Add at least 3 tests for edge cases in `test/challenge_tests.cpp`.

Suggested edge cases:
- Empty stack/queue behavior.
- `rotate(0)`, `rotate(size)`, `rotate(size + 1)`.
- Palindrome true/false with odd and even sizes.

## Person 2: Linked List + Hash Table 30 min

Files:
- `include/datastructures/linked_list.hpp`
- `include/datastructures/hash_table.hpp`

Tasks:
1. Implement `LinkedList::push_back`.
2. Implement `LinkedList::erase_first`.
3. Implement `LinkedList::to_vector`.
4. Implement `HashTable::insert`, `HashTable::contains`, `HashTable::erase`, and `HashTable::bucket_count`.
5. Add at least 3 tests in `test/challenge_tests.cpp`.

Suggested edge cases:
- Erase from empty list.
- Erase head, middle, and missing value.
- `to_vector` on empty and multi-node lists.
- Duplicate keys in the hash table.
- Collisions and rehashing.
- Erasing a missing key from a non-empty table.

## Person 3: Binary Search Tree 90 min

Files:
- `include/datastructures/binary_search_tree.hpp`

Tasks:
1. Implement `BinarySearchTree::inorder`.
2. Implement `BinarySearchTree::height`.
3. Implement `BinarySearchTree::remove`.
4. Add at least 6 tests in `test/challenge_tests.cpp`.
5. Use the hash table tests as a model for thinking about harder edge-case design.
6. Improve the tree behavior or add one extra helper if time remains, such as `min_value`, `max_value`, or an iterative traversal helper.

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
5. The 90-minute person documents one extra improvement they made beyond the basic checklist.
