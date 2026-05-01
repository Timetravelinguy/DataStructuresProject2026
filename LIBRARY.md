# Data Structures Library - User Guide

Welcome to **Data Structures Project 2026**, a lightweight C++ template library providing five essential data structures for efficient data organization and manipulation.

---

## Quick Start

All data structures are in the `ds::` namespace. Include the headers from `include/datastructures/`:

```cpp
#include "datastructures/stack.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/linked_list.hpp"
#include "datastructures/hash_table.hpp"
#include "datastructures/binary_search_tree.hpp"
```

---

## 1. Stack — Last-In-First-Out (LIFO)

A stack is like a stack of plates: the last plate added is the first one you remove.

**Use Cases:** Undo/redo functionality, expression evaluation, depth-first search, backtracking.

### API

```cpp
ds::Stack<int> stack;

// Add an item to the top
stack.push(42);

// Remove the top item
stack.pop();

// Peek at the top without removing
int top_value = stack.top();  // throws if empty

// Check if empty
if (!stack.empty()) { /* ... */ }

// Get current size
size_t n = stack.size();

// NEW: Query operations
bool has_it = stack.contains(42);              // Is 42 in the stack?
size_t pos = stack.index_of(42);               // Position from bottom (0-based), or npos if not found
stack.reverse();                               // Flip the stack order in-place
```

### Example

```cpp
ds::Stack<char> history;
history.push('a');
history.push('b');
history.push('c');

std::cout << history.top() << "\n";           // Prints: c
std::cout << history.contains('b') << "\n";   // Prints: 1 (true)
std::cout << history.index_of('b') << "\n";   // Prints: 1

history.reverse();
std::cout << history.top() << "\n";           // Prints: a
```

---

## 2. Queue — First-In-First-Out (FIFO)

A queue is like a line at a store: the first person in is the first person served.

**Use Cases:** Task scheduling, breadth-first search, printer queues, customer service lines.

### API

```cpp
ds::Queue<int> queue;

// Add an item to the back
queue.enqueue(10);

// Remove the front item
queue.dequeue();

// Peek at the front without removing
int front_value = queue.front();  // throws if empty

// Check if empty
if (!queue.empty()) { /* ... */ }

// Get current size
size_t n = queue.size();

// NEW: Advanced operations
queue.rotate(2);                      // Move front to back 2 times
bool is_sym = queue.is_palindrome();  // Does it read same forwards and backwards?
```

### Example

```cpp
ds::Queue<int> line;
line.enqueue(1);
line.enqueue(2);
line.enqueue(1);

std::cout << line.is_palindrome() << "\n";  // Prints: 1 (true)

line.rotate(1);
std::cout << line.front() << "\n";          // Prints: 2 (1 moved to back)
```

---

## 3. Linked List — Flexible Sequential Storage

A linked list chains nodes together. Each node knows the next node's address.

**Use Cases:** Frequent insertions/deletions, unknown size in advance, memory fragmentation concerns.

### API

```cpp
ds::LinkedList<int> list;

// Add to the front (efficient)
list.push_front(1);

// Add to the end (O(n) scan required)
list.push_back(3);

// Check if empty or get size
if (!list.empty()) { /* ... */ }
size_t n = list.size();

// NEW: List operations
bool removed = list.erase_first(2);   // Remove first occurrence; false if not found
std::vector<int> vec = list.to_vector();  // Export as vector for iteration
```

### Example

```cpp
ds::LinkedList<std::string> names;
names.push_front("Charlie");
names.push_back("Alice");
names.push_back("Bob");

auto all = names.to_vector();  // ["Charlie", "Alice", "Bob"]

names.erase_first("Alice");
all = names.to_vector();       // ["Charlie", "Bob"]
```

---

## 4. Hash Table — Fast Membership Checking

A hash table uses a hash function to map values to buckets, enabling O(1) average-case lookup.

**Use Cases:** Membership testing, caching, deduplication, symbol tables.

### API

```cpp
ds::HashTable<int> table;  // Bucket count defaults to 8

// Create with custom bucket count
ds::HashTable<int> custom(16);

// Add a value (duplicates ignored)
table.insert(42);

// Check if value exists
bool found = table.contains(42);

// Remove a value; returns true if removed, false if not found
bool removed = table.erase(42);

// Query structure
size_t buckets = table.bucket_count();  // Number of separate chains
size_t total = table.size();             // Number of stored values
```

### Example

```cpp
ds::HashTable<int> seen;
seen.insert(100);
seen.insert(200);

if (seen.contains(100)) {
    std::cout << "Already processed 100\n";
}

seen.erase(100);
std::cout << (seen.contains(100) ? "still there" : "gone") << "\n";  // gone
```

---

## 5. Binary Search Tree — Sorted Organization

A BST keeps values sorted in a tree structure, enabling fast search and range queries.

**Use Cases:** Sorted data, range queries, in-order traversal, efficient remove-and-insert.

### API

```cpp
ds::BinarySearchTree<int> tree;

// Insert a value (duplicates ignored, auto-sorted)
tree.insert(50);
tree.insert(30);
tree.insert(70);

// Check if value exists
bool found = tree.contains(40);

// NEW: Tree operations
std::vector<int> sorted = tree.inorder();  // All values in sorted order
size_t depth = tree.height();               // Longest path from root to leaf
bool removed = tree.remove(30);             // Remove a value (handles all cases)
```

### Example

```cpp
ds::BinarySearchTree<int> ages;
ages.insert(45);
ages.insert(23);
ages.insert(67);
ages.insert(12);

auto all_sorted = ages.inorder();  // [12, 23, 45, 67]

std::cout << "Tree depth: " << ages.height() << "\n";  // 3

ages.remove(23);
auto updated = ages.inorder();     // [12, 45, 67]
```

---

## Type Support

All data structures are **templates**. Use any type that supports the operations you need:

```cpp
ds::Stack<double> prices;
ds::Queue<std::string> names;
ds::LinkedList<MyClass> objects;
ds::HashTable<char> letters;
ds::BinarySearchTree<float> measurements;
```

---

## Exception Safety

- **Empty container access** throws `std::underflow_error`:
  ```cpp
  ds::Stack<int> empty;
  empty.top();  // Throws: "Cannot get top of an empty stack"
  ```

- **Other operations** return safe values or false on failure:
  ```cpp
  stack.index_of(999);  // Returns `npos` if not found
  queue.rotate(0);      // Safe: no operation
  list.erase_first(x);  // Returns false if not found
  ```

---

## Performance Notes

| Operation | Stack | Queue | LinkedList | HashTable | BST |
|-----------|-------|-------|-----------|-----------|-----|
| Insert | O(1) | O(1) | O(n) | O(1) avg | O(log n) avg |
| Lookup | O(n) | O(n) | O(n) | O(1) avg | O(log n) avg |
| Remove | O(1) | O(1) | O(n) | O(1) avg | O(log n) avg |

---

## Compilation

Include `include/datastructures/` in your compiler's include path:

```bash
g++ -I include myprogram.cpp -o myprogram
```

Or use CMake (see `CMakeLists.txt` for build configuration).

---

## License & Credits

This library was built as an educational project demonstrating core data structures in C++.

