#pragma once

#include "../Entities/Questions/Question.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"

#include <fstream>
#include <vector>

std::vector<Question*> InsertFromFileIntoQuestionsNum();

std::vector<Question*> InsertFromFileIntoQuestionsMultip();

// make either a class or just a function to insert lines from a file into an object of type question
// emplace back into question with NumericQuestion and MultipleAnswerQuestion separately

// the function for NumericQuestion should look like this:
// open file (try/catch if found or not)
// read first line, second, and third (these are labeled "0. Question", "Answer", "\n" for introduction
// when entering loop, for the first line ignore until the first letter is reached 
// and always ignore the third line

// the function for MultipleAnswerQuestion should look like this:
// same as above but instead of second and third line we have second, third, fourth, fifth 
// as choices and sixth as correct answer. ignore until first letter (or digit idk)
// always ignore seventh line

// etc.

