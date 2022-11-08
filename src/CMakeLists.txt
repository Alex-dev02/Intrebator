cmake_minimum_required(VERSION 3.16)

add_library(test SHARED
    main.cpp
)

target_include_directories(test PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
