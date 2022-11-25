#pragma once

#include <string>

class Question {
public:
	Question() = default;
	Question(std::uint32_t id, const std::string& question);
	Question(const std::string& question);

	virtual ~Question() = default;

public:

	std::uint32_t GetId() const;
	const std::string& GetQuestion() const;

	void SetId(std::uint32_t id);
	void SetQuestion(const std::string& question);

private:
	std::uint32_t m_id;
	std::string m_question;

};
