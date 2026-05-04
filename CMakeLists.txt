cmake_minimum_required(VERSION 3.16)
project(DataStructuresProject2026 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ds_core INTERFACE)

target_include_directories(ds_core INTERFACE include)

add_executable(DataStructuresProject2026
	src/main.cpp
)

target_link_libraries(DataStructuresProject2026 PRIVATE ds_core)

add_executable(demo
	demo.cpp
)

target_link_libraries(demo PRIVATE ds_core)

add_executable(book_manager
	src/book_manager/main.cpp
	src/book_manager/library.cpp
)

target_link_libraries(book_manager PRIVATE ds_core)

enable_testing()

add_executable(ds_tests
	test/test_main.cpp
)

target_link_libraries(ds_tests PRIVATE ds_core)
add_test(NAME ds_tests COMMAND ds_tests)

add_executable(ds_challenge_tests
	test/challenge_tests.cpp
	src/book_manager/library.cpp
)

target_link_libraries(ds_challenge_tests PRIVATE ds_core)
target_include_directories(ds_challenge_tests PRIVATE src/book_manager)
add_test(NAME ds_challenge_tests COMMAND ds_challenge_tests)

