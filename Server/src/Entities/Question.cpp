#include "../../include/Entities/Question.hpp"

Question::Question(std::uint32_t id, const std::string& question)
	: m_id(id),
	m_question(question)
{}

Question::Question(const std::string& question)
	: m_question(question)
{}

const std::string& Question::GetQuestion() const {
	return m_question;
}

void Question::SetQuestion(const std::string& question)
{
	m_question = question;
}

std::uint32_t Question::GetId() const
{
	return m_id;
}

void Question::SetId(std::uint32_t id)
{
	m_id = id;
}
