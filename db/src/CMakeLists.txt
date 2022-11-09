cmake_minimum_required(VERSION 3.16)

add_library(libDatabase SHARED
    User.cpp
)

target_link_libraries(libDatabase PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(libDatabase PRIVATE sqlite_orm::sqlite_orm)
