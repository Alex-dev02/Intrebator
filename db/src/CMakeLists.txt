cmake_minimum_required(VERSION 3.16)

add_library(libDatabase SHARED
    User.cpp,
    Question.cpp
)

# target_link_libraries(libDatabase PRIVATE sqlite_orm::sqlite_orm)
