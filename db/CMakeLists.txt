cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find_package(SqliteOrm CONFIG REQUIRED)

add_subdirectory(src)

target_include_directories(libDatabase PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/entities>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
)
