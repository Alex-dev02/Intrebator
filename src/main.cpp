#include <iostream>
#include <sqlite_orm/sqlite_orm.h>


#include <db/include/Database.hpp>
#include <db/entities/User.hpp>

#include <string>

int main() {
    User u{1, "Alex"};
    DB::m_storage.replace(u);
    std::cout << "Hello world!";
}
