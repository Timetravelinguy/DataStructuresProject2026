# Final Demo Script

This script is written for a short live presentation. It assumes one person is driving the keyboard while others explain their parts.

## 1. Opening

Say:

"Our project is a data structures library and book manager built in C++17. We implemented our own stack, queue, linked list, hash table, and binary search tree, then used them in a menu-driven book manager initialized with sample data."

Then point out the main ideas:

- The challenge structures live in `include/datastructures/`.
- The book manager lives in `src/book_manager/`.
- The program is initialized with seeded sample data for the demo.

## 2. Show the Program

Start `book_manager.exe` and show the main menu.

Say:

"We added a real interactive console flow, cancellation support, validation, and help text so the program is easier to use during a live demo."

## 3. Demo the Required Book Features

Show these actions in order:

1. Add a new book.
2. Search by Book ID.
3. Search by title, author, or category.
4. Borrow a book and show that its status changes.
5. Return the same book and show it becomes available again.
6. Remove a book by Book ID.

Suggested script while demoing:

- "Each book stores ID, title, author, year, category, and status."
"Borrowing and returning update the status in memory for the running session."
- "Removal is done by Book ID, which matches the project spec."

## 4. Notes on Program State

Explain that the program starts with a seeded collection of sample books for the demo. Changes are kept in memory during the run.

## 5. Show the Custom Data Structures

Switch to a few implementation files and explain the design choices:

- Stack uses `std::vector` for simple LIFO behavior.
- Queue uses `std::deque` for fast front and back operations.
- Linked list uses raw pointers and manual cleanup.
- Hash table uses separate chaining with dynamic bucket arrays.
- Binary search tree stores books in sorted order and supports removal.

Say:

"We built the structures to show the core mechanics, not just wrap STL containers."

## 6. Close

End with:

"Our project meets the book manager requirements and the data structure challenge requirements. The main tradeoff we made was choosing simple, explainable implementations over highly optimized production code."

## Quick Timing Version

- 30 seconds: project overview
- 2 minutes: live book manager demo
- 1 minute: validation and demo state
- 1 minute: data structure explanation
- 30 seconds: wrap-up

## Backup Plan

If the live demo gets blocked, show these screenshots or file references instead:

- `src/book_manager/library.cpp`
- `src/book_manager/library.hpp`
- `include/datastructures/hash_table.hpp`
- `include/datastructures/queue.hpp`
