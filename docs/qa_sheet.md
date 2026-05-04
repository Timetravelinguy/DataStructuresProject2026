# Final Q&A Sheet

Short answers are better in the presentation. Keep each response to one or two sentences unless the teacher asks for more detail.

## Project Questions

### 1. What was the main goal of the project?

We built custom data structures in C++ and used them in a practical book manager so we could show both implementation knowledge and a working application.

### 2. Why did you avoid using STL for everything?

We still use small STL helpers where appropriate, but the core assignment was to demonstrate that we understand how the data structures work internally.

### 3. What makes your hash table educational?

It uses manual bucket allocation and separate chaining, so collisions are handled with linked lists instead of hiding the mechanics behind a library container.

### 4. Why does the linked list use raw pointers?

Because the point of the assignment is to practice manual memory management, pointer traversal, and cleanup.

### 5. Why did you choose a deque for the queue?

Because front and back operations are both efficient, which matches a real FIFO queue well.

### 6. Why did you choose a vector for the stack?

Because stack operations only need the back of the container, and vector gives simple and fast push and pop behavior.

### 7. Why is the book manager saved to files?

So the data persists between runs, which makes the program feel like a real application instead of a temporary demo.

### 8. What happens if the user enters invalid input?

The program validates the input, shows an error message, and asks again instead of crashing.

### 9. What happens if the user types cancel?

The current operation stops and the program returns to the menu.

### 10. How do borrow and return work?

Borrow marks a book as borrowed and Return marks it as available again. The status is saved to disk after the change.

### 11. How do you remove a book?

Books are removed by Book ID, which matches the required spec and avoids ambiguous title matches.

### 12. What was the hardest part of the project?

The hardest part was balancing clean classroom-friendly code with correct memory management, persistence, and user input handling.

### 13. What tradeoff did you make in the hash table?

We used separate chaining because it is easier to explain and easier to delete from than open addressing.

### 14. What tradeoff did you make in the tree?

The binary search tree keeps books sorted and easy to traverse, but removal is more complex than in a flat container.

### 15. Why are there 30 sample books?

That satisfies the project requirement for a preloaded collection and makes the demo more realistic.

### 16. What would you improve next if you had more time?

We would add search filters, richer reporting, and possibly a more advanced balancing strategy for the tree.

## Quick One-Line Answers

- "We implemented the structures ourselves."
- "We used persistence so the program keeps its state."
- "We validated input to make the console safer."
- "We chose simple structures that are easy to defend in class."
