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
- The `src/datastructures/*.cpp` files are there for explicit template instantiation.
- `docs/team_work_split.md` explains the class challenge split.

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

