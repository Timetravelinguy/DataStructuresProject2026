# Data Structure Code Walkthrough

This walkthrough explains how each data structure in this project is implemented and what to say when presenting it.

---

## 1. Stack (`include/datastructures/stack.hpp`)

### Storage
- Uses `std::vector<T> data_`.
- Top of stack is the **back** of the vector.

### Core operations
- `push(value)`: `data_.push_back(value)`
- `pop()`: throws `std::underflow_error` if empty, else `pop_back()`
- `top()`: throws `std::underflow_error` if empty, else returns `back()`
- `empty()`, `size()`: direct vector queries

### Extra operations
- `contains(value)`: linear scan
- `index_of(value)`: returns first index from bottom, else `npos`
- `reverse()`: uses `std::reverse`

### Complexity (typical)
- `push`: O(1) amortized
- `pop`, `top`, `empty`, `size`: O(1)
- `contains`, `index_of`, `reverse`: O(n)

---

## 2. Queue (`include/datastructures/queue.hpp`)

### Storage
- Uses `std::deque<T> data_`.
- Front of queue is `data_.front()`, back is `data_.back()`.

### Core operations
- `enqueue(value)`: `push_back`
- `dequeue()`: throws `std::underflow_error` if empty, else `pop_front`
- `front()`: throws `std::underflow_error` if empty
- `empty()`, `size()`: direct deque queries

### Extra operations
- `rotate(k)`: moves front element to back `k` times (with `k % size`)
- `is_palindrome()`: compares mirrored positions from both ends

### Complexity (typical)
- `enqueue`, `dequeue`, `front`, `empty`, `size`: O(1)
- `rotate(k)`: O(k)
- `is_palindrome`: O(n)

---

## 3. Linked List (`include/datastructures/linked_list.hpp`)

### Storage
- Custom singly linked node:
  - `Node { T value; Node* next; }`
- Head pointer: `head_`
- Element count: `size_`

### Memory management
- Destructor walks list and `delete`s every node.
- Copy constructor/assignment deleted to avoid accidental shallow copies.

### Core operations
- `push_front(value)`: allocate new head node
- `push_back(value)`: traverse to tail, append node
- `erase_first(value)`: pointer-to-pointer traversal, deletes first match
- `to_vector()`: converts list contents to `std::vector<T>`
- `empty()`, `size()`: O(1) checks

### Complexity (typical)
- `push_front`: O(1)
- `push_back`: O(n)
- `erase_first`: O(n)
- `to_vector`: O(n)
- `empty`, `size`: O(1)

---

## 4. Hash Table (`include/datastructures/hash_table.hpp`)

### Storage
- Separate chaining with manual buckets:
  - `Node** buckets_`
  - each bucket is a linked chain of `Node`
- Tracks:
  - `bucket_count_`
  - `size_`

### Memory management
- Constructor allocates bucket array and initializes each bucket to `nullptr`.
- Destructor walks every chain and deletes all nodes, then deletes bucket array.
- Copy constructor/assignment deleted (manual ownership).

### Core operations
- `bucket_index(value)`: `std::hash<T>{}(value) % bucket_count_`
- `insert(value)`: skip duplicates; insert at head of chain
- `contains(value)`: scan one bucket chain
- `erase(value)`: remove from chain while maintaining links
- `bucket_count()`, `size()`: accessors

### Complexity (typical)
- Average `insert`, `contains`, `erase`: O(1)
- Worst-case (heavy collisions): O(n)

---

## 5. Binary Search Tree (`include/datastructures/binary_search_tree.hpp`)

### Storage
- Custom node:
  - `Node { T value; Node* left; Node* right; }`
- Root pointer: `root_`

### Memory management
- Destructor recursively deletes left and right subtrees, then node.
- Copy constructor/assignment deleted.

### Core operations
- `insert(value)`: iterative traversal using `Node**` until insertion point
- `contains(value)`: iterative search by BST ordering
- `inorder()`: recursive traversal (left, node, right) into vector
- `height()`: recursive max depth
- `remove(value)`:
  - case 1: no left child
  - case 2: no right child
  - case 3: two children (replace with inorder successor)

### Complexity (typical)
- Average `insert`, `contains`, `remove`: O(log n)
- Worst-case (unbalanced): O(n)
- `inorder`: O(n)
- `height`: O(n)

---

## How these structures are used in the book manager

- `BinarySearchTree<Book>`: main inventory and sorted display
- `HashTable<long long>`: fast Book ID existence checks
- `Stack<Book>`: recently viewed history
- `Queue<Book>`: checkout queue behavior
- `LinkedList<Book>`: wishlist-style mirror of queued books

This mapping helps explain why all five structures are present in one project.
