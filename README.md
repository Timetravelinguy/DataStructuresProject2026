# Data Structures Project 2026

This repo is a C++17 data structures project with five core structures: stack, queue, linked list, hash table, and binary search tree. The code is set up for class use.
## What’s in here

- `Stack` for last-in, first-out behavior
- `Queue` for first-in, first-out behavior
- `LinkedList` for basic pointer-based list operations
- `HashTable` for fast lookups with separate chaining
- `BinarySearchTree` for sorted storage and traversal

There are also two small apps in the repo:

- `src/main.cpp` is the simple project shell
- `src/book_manager/` contains the book manager CLI that uses the data structures in a more realistic way

## Build

If you are using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

After building, the executables are in `build/Debug`:

```bash
.\demo.exe
.\DataStructuresProject2026.exe
.\book_manager.exe
```

`demo.exe` is the quick sample program. `DataStructuresProject2026.exe` is the small shell app. `book_manager.exe` is the interactive CLI.

## Notes on the code

- Public declarations live in `include/datastructures/`.
- All data structures are C++17 templates—they work with any type.
- `LIBRARY.md` has the full API reference.
- `docs/team_work_split.md` explains the class challenge split.

## Design Choices

### Overall Architecture

**C++17 Templates**
- All five data structures are implemented as generic templates (`Stack<T>`, `Queue<T>`, etc.).
- Rationale: Enables type safety, reusability, and lets your code work with `int`, `std::string`, custom objects, or any type.
- Trade-off: Template code lives in headers (no separate compilation), but that's standard for C++ templates.

**Header-Only Library**
- Implementations go directly in `.hpp` files. No separate `.cpp` instantiation files.
- Rationale: Simpler to understand, easier to distribute
- How it works in CMake: `ds_core` is an `INTERFACE` library—it's pure headers, no compilation step.

**Single File Per Structure**
- One header per data structure. No duplicate files, no `.impl.hpp` companion files.
- Rationale: Clean, single source of truth, no confusion about where code lives.

### Person 1: Stack & Queue

**Stack: Vector-Based Implementation**
- Uses `std::vector<T>` for storage.
- Rationale: O(1) push and pop at the back, simple to implement, cache-friendly.
- Methods: `push()`, `pop()`, `top()`, `empty()`, `size()`, `contains()`, `reverse()`.

**Queue: Deque-Based with Modulo Rotation**
- Uses `std::deque<T>` internally, implements rotation using modulo arithmetic.
- Rationale: Deques are efficient for front/back operations. Modulo rotation avoids shifting elements.
- Methods: `enqueue()`, `dequeue()`, `front()`, `empty()`, `size()`, `rotate()`, `is_palindrome()`.

### Person 2: LinkedList & HashTable

**LinkedList: Pointer-Based Nodes**
- Manual node allocation with `new` and cleanup with `delete`.
- Each node holds data and a pointer to the next node.
- Rationale: Traditional linked list implementation, lets students understand pointers and dynamic memory.
- Methods: `push_front()`, `push_back()`, `erase_first()`, `to_vector()`, `empty()`, `size()`.

**HashTable: Separate Chaining with Manual Memory Management**
- Implements a dynamic bucket array (`Node** buckets_`) allocated with `new`/`delete`.
- Each bucket is a linked list of custom `Node` structs (pointer-based, not STL containers).
- Collision resolution: separate chaining—insert at head of bucket chain in O(1), search traverses chain in O(n) worst case.
- Hash function: `std::hash<T>` (standard library, no need to reimplement cryptographic hashing).
- Manual destructor traverses all chains and deallocates every node.
- Copy constructor/assignment deleted (to prevent memory errors with manual allocation).
- Rationale: Full implementation from first principles—dynamic allocation, pointer management, memory cleanup—unambiguous proof of understanding.
- Methods: `insert()`, `contains()`, `erase()`, `bucket_count()`, `size()`.

### Person 3: Binary Search Tree

**Recursive Traversal and Operations**
- All traversals (in-order, pre-order) and operations (height, removal) use recursion.
- Rationale: Recursive solutions are elegant and natural for tree problems.
- In-order traversal returns elements in sorted order.
- Removal uses successor logic: replaces removed node with the smallest value in the right subtree.
- Methods: `insert()`, `contains()`, `inorder()`, `height()`, `remove()`.

### Book Manager CLI: Real-World Integration

**Book Type with Operators**
- `Book` struct is copyable and comparable (overloaded `==` and `<`).
- Rationale: Allows `Book` objects to be stored in hash tables and binary search trees without extra work.

**LibraryManager Wrapper**
- Single class that owns all five data structures internally.
- Rationale: Shows how real applications combine multiple data structures to solve a problem.
- Demonstrates: Stack (undo/redo), Queue (processing queue), LinkedList (custom storage), HashTable (fast lookup), BST (sorted inventory).

**Interactive Menu**
- Seven operations: Add, Remove, View All, Search, History, Dequeue, ISBN Lookup.
- Rationale: Practical example that students can run and extend, making the learning concrete.

### Design Justification: STL vs. Manual Implementation

**Stack & Queue use STL containers** (`std::vector`, `std::deque`)
- Focuses on the *interface and behavior* of these structures rather than reinventing memory management.
- Shows judgment: use the right tool for the job (in production code, this is correct).
- Still demonstrates algorithmic understanding: rotation with modulo, LIFO/FIFO semantics.

**LinkedList, HashTable, and BST are implemented from scratch**
- Custom pointer-based nodes for LinkedList (manual memory management, `new`/`delete`).
- Dynamic bucket array for HashTable (`Node**` with manual allocation and chain traversal).
- Recursive operations for BST (height, in-order, removal with successor logic).
- This approach shows we understand pointers, dynamic memory, and complex data structure logic.

**Mixed approach is realistic.** Professional code uses both: STL for simple structures, custom implementations for 
specialized problems that benefit from low-level control.

## Project layout

```text
.
├── include/datastructures/
├── src/datastructures/
├── src/main.cpp
├── src/book_manager/
├── demo.cpp
├── test/
├── docs/
├── LIBRARY.md
└── CMakeLists.txt
```

## Testing

```bash
cd build
ctest --output-on-failure
```

