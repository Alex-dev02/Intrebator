#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include "../entities/User.hpp"

using namespace sqlite_orm;

namespace DB{
    auto m_storage = make_storage("db.sqlite",
                make_table("user",
                    make_column("id", &User::SetId, &User::GetId, autoincrement(), primary_key()),
                    make_column("name", &User::SetName, &User::GetName))
    );
}