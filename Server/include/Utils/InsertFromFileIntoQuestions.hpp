#pragma once

#include "../Entities/Questions/Question.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"

#include <fstream>
#include <vector>

std::vector<NumericQuestion> ReadNumericQuestionsFromFile();

std::vector<MultipleAnswerQuestion> ReadMultipleAnswerQuestionsFromFile();
