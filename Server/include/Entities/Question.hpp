# pragma once

#include <string>

class Question {
public:
    Question(const std::string& question);

    const std::string& GetQuestion() const;
    void SetQuestion(const std::string& question);
    
    ~Question() = default;

    const std::uint8_t GetId() const;

    void SetId(const std::uint8_t id);
private:
    std::uint8_t m_id;
    std::string m_question;

};
