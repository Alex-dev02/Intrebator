#include <iostream>
#include <sqlite_orm/sqlite_orm.h>


#include <db/include/Database.hpp>
#include <db/entities/User.hpp>

#include <string>

int main() {
    auto storage = Database::DB();
    User u("Alex");
    storage.insert(u);
    std::cout << "Hello world!";
}
