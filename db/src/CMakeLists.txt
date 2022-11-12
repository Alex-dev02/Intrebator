cmake_minimum_required(VERSION 3.16)

add_library(libDatabase STATIC
    User.cpp
    Question.cpp 
    NumericQuestion.cpp
    MultipleAnswerQuestion.cpp
)

target_link_libraries(libDatabase PRIVATE sqlite_orm::sqlite_orm)
