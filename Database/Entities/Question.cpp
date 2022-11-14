#include "../entities/Question.hpp"

Question::Question(const std::string &question)
    :m_question(question)
    {}

const std::string &Question::GetQuestion() const {
    return m_question;
}