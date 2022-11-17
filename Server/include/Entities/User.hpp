#pragma once
#include <string>

class User {
public:

    User() = default;
    User(unsigned int id, const std::string& name);

    std::string GetName() const;
    unsigned int GetId() const;

    void SetId(unsigned int id);
    void SetName(const std::string& name);

private:
    unsigned int id;
    std::string name;

};
