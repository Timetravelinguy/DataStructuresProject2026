# Presentation Guide (Team Version)

This guide is meant to sound natural for a student presentation.

## 1. Project summary (30-45 seconds)

Say:

"We built a Library Book Management System in C++ and used our own data structures to support the required operations."

Mention:
- Book record fields
- Menu-driven CLI
- 30 preloaded sample books

## 2. Teammate talking points

### Person 1 (Stack + Queue)
- Stack: LIFO, built with `std::vector`
- Queue: FIFO, built with `std::deque`
- Extra functions: `contains`, `index_of`, `reverse`, `rotate`, `is_palindrome`
- Where used in app:
  - Stack = recently viewed books
  - Queue = checkout queue

### Person 2 (LinkedList + HashTable)
- Linked list: custom node pointers (`new`/`delete`)
- Hash table: separate chaining + bucket array
- Where used in app:
  - Hash table = fast Book ID lookup
  - Linked list = wishlist mirror for queue items

### Person 3 (BST + App Integration)
- BST stores books in sorted order
- In-order traversal used for "display all books"
- Remove handles leaf, one-child, and two-child cases
- Integrated menu operations: add/remove/search/borrow/return

## 3. Required features checklist (demo order)

1. Add a book  
2. Search by Book ID  
3. Search by title or category  
4. Display all books  
5. Borrow book  
6. Return book  
7. Remove by Book ID  

## 4. Quick Big-O lines to memorize

- Stack push/pop/top: `O(1)`  
- Queue enqueue/dequeue/front: `O(1)`  
- Linked list search/erase: `O(n)`  
- Hash table search: average `O(1)`, worst `O(n)`  
- BST search/insert/remove: average `O(log n)`, worst `O(n)`  
- BST inorder traversal: `O(n)`

## 5. Common questions and short answers

**Why not use STL for everything?**  
Because the assignment is about understanding how structures work internally.

**Why HashTable + BST together?**  
Hash table gives fast ID lookup; BST gives sorted output.

**How do you prevent duplicate IDs?**  
Before adding, we check the hash table for existing Book ID.

**What happens on invalid input?**  
Input is validated and errors are shown without crashing.

**How do borrow/return rules work?**  
Borrow fails if already borrowed; return fails if already available.

## 6. What not to overclaim

- Do not claim persistence to file in this version.
- Do not claim balancing tree logic (it is a standard BST).
- Do not claim advanced concurrency/thread safety.

## 7. What we need to know (detailed speaking order)

This section lists every vital topic you should understand, a short explanation to learn the concept, and a short "Say:" line to use during the presentation. Read the explanation first so you know what you're talking about, then use the speech line as a prompt.

1) Project purpose
- Explanation: The project is a Library Book Management System implemented in C++ to demonstrate custom data structures and their use in common operations (add, search, borrow, return, remove).
- Say: "Our project is a Library Book Management System in C++ that uses custom data structures to manage and search book records efficiently."

2) Data model (Book record)
- Explanation: Know each field (ID, title, author, category, borrowed flag, borrower info). Understand why ID is primary key and what fields display in listings.
- Say: "Each book has an ID, title, author, category, and a borrowed status — we use the ID as the key for lookups."

3) Core data structures (for each: short explanation then speaking line)
- Stack (where used)
  - Explanation: LIFO collection for recently viewed books or undo stacks. Implemented with vector for O(1) push/pop.
  - Say: "We used a stack for recently viewed books — newest viewed is on top, implemented with a vector."
- Queue
  - Explanation: FIFO collection for checkout queue; use deque for O(1) enqueue/dequeue.
  - Say: "A queue models the checkout line — first in, first out — implemented with std::deque."
- Linked list
  - Explanation: Simple pointer-based list used when frequent insertions/removals by position are needed; O(n) search.
  - Say: "A linked list stores sequences where we may insert or remove in the middle without reallocating an array."
- Hash table
  - Explanation: Array of buckets + separate chaining for collisions. Primary use: fast Book ID lookup (average O(1)).
  - Say: "We use a hash table for fast Book ID lookups, using separate chaining for collision handling."
- Binary Search Tree (BST)
  - Explanation: Binary tree that keeps books sorted by a key (e.g., title or ID). Useful for ordered traversal (in-order = sorted listing). Not self-balancing.
  - Say: "The BST stores books so we can print them in sorted order via in-order traversal."

4) Demo flow (what to show and why, with talk track)
- Explanation: Follow the required features checklist in the demo order. Explain the goal of each demo step before showing it so viewers know what to look for.
- Say (example for each step):
  - Add a book: "Now we'll add a book to show how new entries are inserted and indexed."
  - Search by ID: "We'll search by ID to demonstrate the hash table lookup."
  - Search by title/category: "This shows how we find books by non-key fields."
  - Display all: "We'll display all books to show the BST in-order traversal output."
  - Borrow/Return: "Now we'll borrow a book, showing validation, and then return it."
  - Remove: "Finally we'll remove a book by ID to show deletion logic across structures."

5) Complexity and trade-offs
- Explanation: Be ready to state Big-O for each structure and note average vs worst-case (e.g., hash table average O(1), worst O(n)). Mention that the BST is not balanced, so worst-case degrades to O(n).
- Say: "Key complexities: hash table lookups average O(1), linked list operations O(n), BST average O(log n) but worst-case O(n) since it's not balanced."

6) Input validation & edge cases
- Explanation: Describe how invalid input is handled, duplicate ID prevention, borrow/return validations, and how deletions update all structures consistently.
- Say: "Inputs are validated; adding checks prevents duplicate IDs and borrow/return operations enforce current status."

7) Testing & sample data
- Explanation: Mention the sample dataset (30 books), how tests or manual checks were performed, and any automated test files if present.
- Say: "We included 30 sample books and tested each operation to verify correctness and edge cases."

8) Team responsibilities & transitions
- Explanation: State which teammate covers which data structures and who performs each demo step; plan handoffs in one-line transitions.
- Say: "I'll cover the stack and queue and then hand off to [Name] for linked list and hash table."

9) Q&A prep (common questions and short answers)
- Explanation: Review the 'Common questions' section. Have short, honest answers ready for trade-offs, design choices, and limitations.
- Say: "If asked about persistence or balancing, be honest: persistence isn't implemented and the BST is not self-balancing."

10) Closing line
- Explanation: Prepare a concise summary and next steps (future improvements): file persistence, balancing, more tests.
- Say: "In summary, we built a functioning library management system that demonstrates core data structure implementations; next steps could include persistence and a balanced tree."

Notes:
- Practice the order so explanations come before the short spoken lines.
- Keep each spoken line to one or two sentences; use the explanation to expand when answering questions.
