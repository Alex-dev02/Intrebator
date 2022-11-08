cmake_minimum_required(VERSION 3.16)
project(Intrebator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(db)
add_subdirectory(src)

target_link_libraries(test PRIVATE libDatabase)

add_executable(test_exe src/main.cpp)

target_link_libraries(test_exe PRIVATE libDatabase)
