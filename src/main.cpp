#include <iostream>

#include <db/entities/User.hpp>
#include <db/include/Database.hpp>

#include <string>

int main() {
    User u{1, "Alex"};
    DB::m_storage.sync_schema();
    auto inserted_id = DB::m_storage.insert(u);
    auto user = DB::m_storage.get<User>(inserted_id);
    std::cout << user.GetName();
    std::cout << "Hello world!";
}
