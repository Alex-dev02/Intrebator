#include "../../include/Entities/Question.hpp"

Question::Question(const std::string& question)
	:m_question(question)
{}

const std::string& Question::GetQuestion() const {
	return m_question;
}

void Question::SetQuestion(const std::string& question)
{
	m_question = question;
}

const std::uint8_t Question::GetId() const
{
	return m_id;
}

void Question::SetId(const std::uint8_t id)
{
	m_id = id;
}
