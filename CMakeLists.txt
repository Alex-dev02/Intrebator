cmake_minimum_required(VERSION 3.16)
project(Intrebator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(db)
add_subdirectory(src)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE libDatabase)
