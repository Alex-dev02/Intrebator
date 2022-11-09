#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include <string>

#include "../entities/User.hpp"

using namespace sqlite_orm;

class Database final {
public:

    static auto DB() {
        auto storage = make_storage("db.sqlite",
            make_table("user",
                make_column("id", &User::SetId, &User::GetId, autoincrement(), primary_key()),
                make_column("name", &User::SetName, &User::GetName))
        );

        storage.sync_schema();

        return storage;
    }
    
private:

};
