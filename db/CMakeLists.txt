cmake_minimum_required(VERSION 3.16)

add_subdirectory(dependencies)
add_subdirectory(src)

target_include_directories(libDatabase PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
