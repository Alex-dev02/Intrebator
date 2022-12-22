#pragma once

#include "../Entities/Questions/Question.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"

#include <fstream>
#include <vector>

std::vector<Question*> InsertFromFileIntoQuestionsNum();

std::vector<Question*> InsertFromFileIntoQuestionsMultip();
