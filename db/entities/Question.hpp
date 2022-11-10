# pragma once

#include <string>

class Question {
public:
    Question(const std::string& question);
    const std::string& GetQuestion() const;
    
    ~Question() = default;
private:
    std::string m_question;

};
