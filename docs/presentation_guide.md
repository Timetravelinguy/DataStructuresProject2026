# Data Structures Project Presentation Guide

This document provides detailed talking points, technical details, and likely exam/interview questions for each person's portion of the project.

---

## Person 1: Stack & Queue

### Stack Overview

**What You Built**
- A generic `Stack<T>` template using `std::vector<T>` for storage
- LIFO (Last-In-First-Out) behavior
- Located in: [include/datastructures/stack.hpp](../include/datastructures/stack.hpp)

**Key Design Decision: Vector-Based**
- We chose `std::vector` over a linked list
- **Why?** O(1) push/pop at the back, cache-friendly, no pointer overhead
- The vector grows dynamically when full (doubling strategy built into STL)

**Implementation Details**
```cpp
template <typename T>
class Stack {
private:
    std::vector<T> data_;  // All storage here
};
```

**Methods You Implemented**
1. `push(T value)` — Add to back of vector (O(1) amortized)
2. `pop()` — Remove from back (O(1))
3. `top()` — Return last element without removing (O(1))
4. `empty()` — Check if empty (O(1))
5. `size()` — Return element count (O(1))
6. `contains(T value)` — Linear search (O(n))
7. `reverse()` — Reverses stack order (O(n))

**Time Complexity Table**
| Operation | Time | Space |
|-----------|------|-------|
| push      | O(1) amortized | O(n) total |
| pop       | O(1) | — |
| top       | O(1) | — |
| contains  | O(n) | — |
| size      | O(1) | — |

**Real-World Use Cases**
- Undo/redo in editors
- Browser back button history
- Function call stack in CPUs
- Expression evaluation (infix to postfix)

**Likely Questions & Answers**

**Q: Why vector instead of linked list?**
- A: Vectors have better cache locality, simpler memory management, and O(1) push/pop. Linked lists add pointer dereferencing overhead for no benefit here.

**Q: What happens when the vector is full?**
- A: STL vector automatically allocates a larger buffer (typically doubles), copies elements, and frees old memory. This is O(n) but happens rarely, so amortized O(1).

**Q: How would you implement stack without STL?**
- A: Allocate a fixed-size array with a `top_` pointer. Resize manually when full (reallocate, copy, deallocate).

**Q: Is this thread-safe?**
- A: No. Multiple threads could corrupt the vector. You'd need locks or atomic operations.

---

### Queue Overview

**What You Built**
- A generic `Queue<T>` template using `std::deque<T>` for storage
- FIFO (First-In-First-Out) behavior
- Bonus methods: `rotate()` and `is_palindrome()`
- Located in: [include/datastructures/queue.hpp](../include/datastructures/queue.hpp)

**Key Design Decision: Deque-Based with Modulo Rotation**
- We chose `std::deque` (double-ended queue)
- **Why?** O(1) insertion/removal at *both* ends, unlike vector (front removal is O(n))
- Rotation uses modulo arithmetic instead of physically moving elements

**Implementation Details**
```cpp
template <typename T>
class Queue {
private:
    std::deque<T> data_;  // Efficient at both ends
};

// Rotation with modulo (no element movement!)
T rotate() {
    front_index_ = (front_index_ + 1) % data_.size();
    return data_[front_index_];
}
```

**Methods You Implemented**
1. `enqueue(T value)` — Add to back (O(1))
2. `dequeue()` — Remove from front (O(1))
3. `front()` — Peek at front (O(1))
4. `empty()` — Check if empty (O(1))
5. `size()` — Return element count (O(1))
6. `rotate()` — Rotate front element to back (O(1) with modulo trick)
7. `is_palindrome()` — Check if front-to-back equals back-to-front (O(n))

**Time Complexity Table**
| Operation | Time | Space |
|-----------|------|-------|
| enqueue   | O(1) amortized | O(n) total |
| dequeue   | O(1) | — |
| front     | O(1) | — |
| rotate    | O(1) | — |
| is_palindrome | O(n) | O(1) extra |
| size      | O(1) | — |

**The Modulo Rotation Trick**
```cpp
// Without modulo: physically move elements (O(n))
// With modulo: just track a virtual front index
T rotate() {
    front_index_ = (front_index_ + 1) % data_.size();
    return data_[front_index_];
}
```
This is clever—you're virtually rotating without touching the data.

**Real-World Use Cases**
- Print queues (jobs waiting to print)
- Task scheduling (OS processes)
- Breadth-first search (BFS) in graphs
- Customer service lines

**Likely Questions & Answers**

**Q: Why deque instead of vector?**
- A: Deque is optimized for front/back operations. Vector front removal is O(n) because it shifts all elements. Deque uses multiple memory blocks, so front removal is O(1).

**Q: Explain the modulo rotation trick.**
- A: Instead of physically moving all elements to rotate, we just track a `front_index` and use modulo to wrap around. `(front_index + 1) % size` gives us the next front without moving anything. O(1) instead of O(n).

**Q: How does `is_palindrome()` work?**
- A: We compare element at `front_index + i` with element at `front_index - i` (wrapping with modulo), moving inward until we've checked half the queue. O(n) time, O(1) extra space.

**Q: What if the deque is empty and we call dequeue()?**
- A: We throw a `std::out_of_range` exception. Should check `empty()` first.

---

## Person 2: LinkedList & HashTable

### LinkedList Overview

**What You Built**
- A generic `LinkedList<T>` with manual pointer-based nodes
- Singly-linked structure (each node points to next)
- Manual memory management: `new` to allocate, `delete` to free
- Located in: [include/datastructures/linked_list.hpp](../include/datastructures/linked_list.hpp)

**Key Design Decision: Pointer-Based Nodes (Not STL)**
- We wrote custom `Node` structs instead of using `std::list`
- **Why?** Teaches pointer arithmetic, dynamic memory, and manual cleanup—core CS concepts

**Implementation Details**
```cpp
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head_;
};
```

**Methods You Implemented**
1. `push_front(T value)` — Insert at head (O(1))
2. `push_back(T value)` — Insert at tail (O(n) — must traverse to end)
3. `erase_first(T value)` — Remove first occurrence (O(n))
4. `to_vector()` — Convert to `std::vector<T>` (O(n))
5. `empty()` — Check if head is null (O(1))
6. `size()` — Count nodes (O(n))

**Time Complexity Table**
| Operation | Time | Space |
|-----------|------|-------|
| push_front | O(1) | O(1) per call |
| push_back | O(n) | O(1) per call |
| erase_first | O(n) | — |
| to_vector | O(n) | O(n) |
| size | O(n) | — |
| empty | O(1) | — |

**Memory Management**
```cpp
// Destructor: delete every node
~LinkedList() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;           // Manual cleanup
        current = next;
    }
}
```

**Real-World Use Cases**
- Undo/redo stacks (append-only, efficient front removal)
- LRU cache (front/back removal)
- Polynomial arithmetic (each node = coefficient)

**Likely Questions & Answers**

**Q: Why O(n) for push_back?**
- A: We must traverse to the end to find the tail node. With only `head_` pointer, we have no choice. A doubly-linked list with `tail_` pointer would be O(1).

**Q: Why not use `std::list`?**
- A: We want to demonstrate understanding of pointers and memory management. Using STL hides that knowledge.

**Q: What's the difference between this and `std::vector`?**
- A: Linked list: O(1) insertion/removal anywhere (if you have the node), O(n) random access. Vector: O(1) random access, O(n) insertion/removal at arbitrary positions.

**Q: How do you handle memory leaks?**
- A: We manually delete every node in the destructor. If we didn't, memory would leak. For safety, we delete the copy constructor and copy assignment operator to prevent double-deletion bugs.

**Q: Can you add a tail pointer?**
- A: Yes, that would make push_back O(1) instead of O(n). Trade-off: one extra pointer per LinkedList, more code to maintain.

---

### HashTable Overview

**What You Built**
- A generic `HashTable<T>` with manual dynamic memory allocation
- Uses separate chaining, so each bucket can hold a linked list of values
- **This is from scratch**: no STL container is doing the hash table work for us
- Located in: [include/datastructures/hash_table.hpp](../include/datastructures/hash_table.hpp)

**Intuitive Metaphor: A Detective Agency With Filing Cabinets**
- Imagine a detective agency that needs to file suspects by case number.
- The hash function is the receptionist who sends each suspect to a filing cabinet drawer.
- The bucket array is the row of drawers.
- A collision happens when two suspects are sent to the same drawer.
- Separate chaining means the drawer can hold a short line of folders instead of only one folder.
- This is the key idea: the table does not panic when two values collide. It just chains them together in the same bucket.

**Key Design Decision: Manual Bucket Array with Linked List Chains**
- `Node** buckets_` is a dynamically allocated array of pointers to bucket heads.
- Each bucket is the start of a linked chain of nodes.
- Each node stores one value and one `next` pointer.
- This design mirrors the real hash-table idea: fast bucket lookup first, then linear scan only inside that bucket.
- **Why manual?** It proves understanding of pointer-based memory, collision handling, and cleanup instead of hiding everything behind STL.

**Implementation Details**
```cpp
template <typename T>
class HashTable {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node** buckets_;              // Dynamic array of pointers
    std::size_t bucket_count_;
    std::size_t size_;

    std::size_t bucket_index(const T& value) const {
        return std::hash<T>{}(value) % bucket_count_;  // Map hash code into a valid drawer
    }
};
```

**Methods You Implemented**
1. `insert(T value)` — Put the value in the correct bucket chain
2. `contains(T value)` — Check whether the value exists in the table
3. `erase(T value)` — Remove the value if it exists
4. `bucket_count()` — Return how many drawers the table has
5. `size()` — Return how many values are stored total

**How Each Operation Works**

**Insert**
- Compute the hash of the value.
- Use modulo to convert the hash into a bucket index.
- Walk the chain in that bucket to make sure the value is not already there.
- If it is new, create a node and place it at the front of the chain.
- Why front insertion? It is simple and O(1) once the bucket is known.

**Contains**
- Compute the bucket index the same way.
- Walk only that bucket’s chain.
- If one of the nodes matches the value, return true.
- If the chain ends, return false.

**Erase**
- Compute the bucket index.
- Walk the chain while keeping track of the previous node.
- If the target is found, unlink that node and delete it.
- The previous pointer is needed because singly linked lists do not let you jump backward.

**Bucket Count and Size**
- `bucket_count()` is just the number of drawers.
- `size()` is just the total number of values currently stored.
- Both are O(1) because they read stored counters, not the data itself.

**Time Complexity (Average vs. Worst Case)**
| Operation | Average | Worst Case | Notes |
|-----------|---------|------------|-------|
| insert    | O(1)    | O(n)       | Worst: all hash to same bucket |
| contains  | O(1)    | O(n)       | Best: empty bucket, Worst: full chain |
| erase     | O(1)    | O(n)       | Same as contains |
| size      | O(1)    | — | Just return counter |

**Load Factor & Collisions**
- Load factor = `size / bucket_count`
- Think of it like the average number of folders per drawer.
- With 8 buckets and 16 elements, load factor = 2, so each drawer averages about two items.
- Higher load factor means longer chains, which means more detective work per lookup.
- Lower load factor means fewer collisions and faster average lookups.
- Good practice in production: rehash to a larger table when the load factor gets too high.
- We keep the project simpler by not implementing automatic rehashing.

**Collision Intuition**
- A collision does not mean failure.
- It just means two different values got assigned to the same drawer.
- The hash table handles this by making a small linked list inside that drawer.
- So the table stays usable even when collisions happen; it just gets slower as chains get longer.

**Memory Management**
```cpp
// Constructor: allocate bucket array
HashTable(std::size_t bucket_count) {
    buckets_ = new Node*[bucket_count_];
    for (...) buckets_[i] = nullptr;
}

// Destructor: delete all nodes and bucket array
~HashTable() {
    for (int i = 0; i < bucket_count_; ++i) {
        Node* current = buckets_[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;  // Delete each node
            current = next;
        }
    }
    delete[] buckets_;  // Delete bucket array
}
```

**Why the Destructor Matters**
- Every `new Node(...)` must eventually be matched with `delete`.
- If we forget, memory leaks.
- If we accidentally copy the table, two objects could try to delete the same nodes, which is why copying is disabled.
- This is one of the clearest signs that the implementation is real, not just a wrapper around STL.

**Real-World Use Cases**
- Symbol tables in compilers
- Database indexing
- Caching systems
- Language dictionaries (spell check)

**Why Hash Tables Are Useful in Practice**
- They are designed for fast lookups when you know what key you want.
- Compilers use them to remember variable names.
- Databases use similar ideas to jump straight to records.
- Caches use them to check whether something is already stored.
- Dictionaries and spell checkers use them to test membership quickly.

**Likely Questions & Answers**

**Q: What's the difference between separate chaining and open addressing?**
- A: Separate chaining puts collided values into a linked list inside the bucket, like adding folders to the same drawer. Open addressing keeps everything in the main array and searches for another empty slot. Separate chaining is easier to explain, easier to delete from, and handles crowded tables more gracefully.

**Q: What happens if all elements hash to the same bucket?**
- A: Then the hash table turns into one long chain in that bucket, so it behaves like a linked list. Insert, contains, and erase all degrade to O(n). That is the worst case, and it is exactly why good hashing and a reasonable bucket count matter.

**Q: Why not use linear probing instead?**
- A: Separate chaining is easier to reason about for a class project because each bucket can store multiple items cleanly. Linear probing can work well too, but deletion is more subtle because you need tombstones and probing continuity.

**Q: How do you prevent collisions?**
- A: You cannot completely prevent collisions because there are usually more possible values than buckets. The best you can do is reduce them with a good hash function and enough buckets. We use `std::hash<T>` because it is standard and reliable.

**Q: What's the load factor and why does it matter?**
- A: Load factor is the number of stored elements divided by the number of buckets. If it gets high, the chains get longer, so the detective has to search more folders inside each drawer. Lower is faster. In production code, tables usually resize when the load factor gets too high.

**Q: Why delete the copy constructor?**
- A: Because the table owns raw pointers. If two objects shared the same nodes, one destructor would delete memory that the other object still thinks it owns. That would cause dangling pointers and double-free bugs. Deleting copy operations prevents that class of errors.

**Q: Could you use a vector of vectors instead of manual pointers?**
- A: Yes, but that would hide the actual mechanics of a hash table. We wanted to show the real structure: a bucket array, nodes, collision chains, and manual cleanup. That is more educational and easier to defend technically.

**Q: Why is `std::hash` acceptable if the table itself is manual?**
- A: Because the hash table logic is the important part of the assignment. `std::hash` gives us a standard way to convert a key into a number. The rest of the implementation—bucket layout, collision handling, insertion, deletion, and cleanup—is still completely manual.

**Q: Why insert at the head of the chain?**
- A: Head insertion is O(1) once the bucket is found. It avoids traversing the whole chain just to add a new node. If order inside the bucket is not important, head insertion is the simplest and fastest choice.

**Q: What does the detective metaphor actually represent?**

---

## Demo and Q&A

For a ready-to-use live demo script, see [docs/demo_script.md](demo_script.md).

For a concise teacher Q&A sheet, see [docs/qa_sheet.md](qa_sheet.md).
- A: The receptionist is the hash function, the filing cabinets are the buckets, the folders inside a drawer are the collision chain, and the detective searching that drawer is the lookup process. It is just an intuitive way to remember that the hash narrows the search first, then the chain handles collisions.

---

## Person 3: Binary Search Tree

### BST Overview

**What You Built**
- A generic `BinarySearchTree<T>` with recursive operations
- Maintains BST property: left subtree < node < right subtree
- Manual pointer-based nodes (not STL)
- Located in: [include/datastructures/binary_search_tree.hpp](../include/datastructures/binary_search_tree.hpp)

**Key Design Decision: Recursive Implementation**
- All operations use recursion (insert, search, traversal, height, removal)
- **Why?** Natural for tree algorithms, clean code, demonstrates recursion mastery

**Implementation Details**
```cpp
template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Node* root_;
};
```

**Methods You Implemented**
1. `insert(T value)` — Insert maintaining BST property (O(log n) avg, O(n) worst)
2. `contains(T value)` — Search for value (O(log n) avg, O(n) worst)
3. `inorder()` — Return elements in sorted order (O(n))
4. `height()` — Return tree height (O(n))
5. `remove(T value)` — Delete node and rebalance (O(log n) avg, O(n) worst)

**Time Complexity Table (Balanced vs. Skewed)**
| Operation | Balanced | Skewed | Notes |
|-----------|----------|--------|-------|
| insert    | O(log n) | O(n)   | Skewed = linked list |
| contains  | O(log n) | O(n)   | Same |
| height    | O(n)     | O(n)   | Always traverse all |
| inorder   | O(n)     | O(n)   | Always traverse all |
| remove    | O(log n) | O(n)   | Finding + removal |

**Recursive Insert**
```cpp
// Pseudocode
insert_recursive(node, value):
    if node is null:
        create new node with value
    else if value < node.data:
        node.left = insert_recursive(node.left, value)
    else if value > node.data:
        node.right = insert_recursive(node.right, value)
    // else: value already exists, don't insert duplicate
```

**In-Order Traversal (Produces Sorted Order!)**
```cpp
// Pseudocode
inorder(node):
    if node is not null:
        inorder(node.left)         // Left subtree first
        print node.data            // Node value
        inorder(node.right)        // Right subtree last
    // Result: sorted order
```

**Removal: The Tricky Part**
Three cases:
1. **Node has no children** (leaf) — just delete it
2. **Node has one child** — replace with that child
3. **Node has two children** — find successor (smallest in right subtree), replace node data with successor data, delete successor

```cpp
// Pseudocode for case 3:
remove(node, value):
    if value < node.data:
        node.left = remove(node.left, value)
    else if value > node.data:
        node.right = remove(node.right, value)
    else:  // Found it
        if node has two children:
            successor = find_min(node.right)  // Smallest in right subtree
            node.data = successor.data        // Copy successor data
            node.right = remove(node.right, successor.data)  // Delete successor
        else:  // 0 or 1 child
            return child (if exists) or null
```

**Real-World Use Cases**
- Database indexing (B-Trees are variants)
- File systems (directory trees)
- Expression parsing (syntax trees)
- Autocomplete/suggestions (prefix trees/Tries)
- Binary search space partitioning

**Likely Questions & Answers**

**Q: Why is worst-case O(n)?**
- A: If you insert sorted data (1, 2, 3, 4, 5), the tree becomes a linked list skewed right. Every search must traverse the entire list.

**Q: How do you avoid worst-case skew?**
- A: Use self-balancing trees: AVL (height-balanced) or Red-Black (color-balanced). They rebalance on insert/delete to keep height O(log n).

**Q: Explain in-order traversal again.**
- A: Left subtree, then node, then right subtree. For BST, this produces sorted output because all left values < node < all right values.

**Q: How does removal with successor work?**
- A: When a node has two children, we can't just delete it (we'd orphan the children). So we find the next largest value (successor—the smallest in the right subtree), copy its data into the node we're removing, then recursively delete the successor. Now the successor node has at most one child (easy to remove).

**Q: Why not use the predecessor instead of successor?**
- A: Either works. Predecessor = largest in left subtree. We chose successor (smallest in right subtree) but it's arbitrary.

**Q: What's the height of an empty tree?**
- A: Typically -1 or 0 depending on definition. We probably use 0 for empty.

**Q: Can you insert duplicates?**
- A: Our implementation does not allow duplicates. We check `if (existing == value) return`. You could modify it to allow duplicates using `<=` vs. `<`.

**Q: How is this different from a heap?**
- A: BST maintains order (in-order traversal is sorted). Heap only guarantees parent < children (min-heap) or parent > children (max-heap). Heap is not fully ordered. BST: good for search/insertion, Heap: good for priority queues.

---

## Integration & Testing

### How Everything Fits Together

The **Book Manager CLI** demonstrates real-world integration:
- `Stack<Book>` — tracks history (undo)
- `Queue<Book>` — processes dequeue operations
- `LinkedList<Book>` — custom storage
- `HashTable<Book>` — fast ISBN lookup
- `BinarySearchTree<Book>` — sorted by title

Each data structure is genuinely useful—not contrived.

### Running Tests

```bash
cd build/Debug
ctest --output-on-failure
```

This runs `ds_tests.exe` and `ds_challenge_tests.exe` which test each structure's correctness.

### Code Review Points

When presenting code:

1. **Show the Node/container structure** — help audience visualize
2. **Walk through one insertion** — step-by-step example
3. **Mention time complexity** — especially best/average/worst
4. **Explain why you made design choices** — not just "this is what I did"
5. **Demo a real example** — run the code, show it works

---

## Presentation Structure (Per Person: ~5-10 minutes)

**Opening (1 min)**
- "I implemented [data structure]"
- Show the header file location
- Quick definition: what problem does it solve?

**Design (2 min)**
- Container/storage choice and why
- Key algorithm or trick
- Time complexity summary

**Implementation (3 min)**
- Show key methods (insert/search)
- Walk through one example
- Explain memory management (if applicable)

**Demo (2 min)**
- Run demo.exe to show it in action
- Show output

**Q&A (remaining time)**
- Be ready for the "likely questions" above

---

## Red Flags to Avoid

❌ "I don't know why I used vector" — Know your choices  
❌ "I copied this from online" — You should understand every line  
❌ "Uh, I think it's O(n)" — Know your complexity analysis  
❌ "It works, but I don't know why" — Understand the algorithm  
❌ Mispronouncing "hash" as "has" (just kidding, but be confident!)

---

## Final Tips

- **Practice explaining before the presentation.** Explain your code to a friend.
- **Prepare one demo run.** Know what output to expect.
- **Memorize your time complexity table.** This is your go-to reference.
- **Be honest if you don't know.** "That's a great question, I'll look into it" is better than a wrong answer.
- **Show enthusiasm.** You built something real—be proud of it.

Good luck!
