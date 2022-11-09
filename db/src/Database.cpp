#include "../include/Database.hpp"

auto Database::DB() {
    // TO DO
    return sqlite_orm::make_storage("db.sqlite");
}
