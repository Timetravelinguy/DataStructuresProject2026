# Data Structures Project 2026

This is our C++17 final project for EE 3223.  
We built five data structures and used them in a simple Library Book Management CLI.

## What we built

- `Stack<T>` (`include/datastructures/stack.hpp`)
- `Queue<T>` (`include/datastructures/queue.hpp`)
- `LinkedList<T>` (`include/datastructures/linked_list.hpp`)
- `HashTable<T>` (`include/datastructures/hash_table.hpp`)
- `BinarySearchTree<T>` (`include/datastructures/binary_search_tree.hpp`)

## Book manager

Code is in `src/book_manager/`.

Book fields:
- Book ID (integer)
- Title
- Author
- Year
- Category
- Status (Available/Borrowed)

Menu supports:
- Add book
- Remove by Book ID
- Search by Book ID
- Search by title/category
- Display all books
- Borrow / Return
- Exit

At startup, the manager seeds 30 sample books.

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

From `build/Debug` (or your generator output folder):

```bash
.\book_manager.exe
.\ds_tests.exe
.\ds_challenge_tests.exe
```

## Tests

```bash
cd build
ctest --output-on-failure
```

## Team split

See `docs/team_work_split.md` for who handled which files.
