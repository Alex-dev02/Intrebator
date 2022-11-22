#pragma once
#include <string>

class User {
public:

    User() = default;
    User(unsigned int id, const std::string& name);

    const std::string& GetName() const;
    unsigned int GetId() const;

    void SetId(std::uint32_t id);
    void SetName(const std::string& name);

private:
    unsigned int m_id;
    std::string m_name;

};
