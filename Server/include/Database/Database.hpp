#pragma once

#include "sqlite_orm/sqlite_orm.h"



class Database {


    void function() {
        using namespace sqlite_orm;

        auto storage = make_storage("db.sqlite",
            make_table("users",
                make_column("id", &User::GetId, &User::SetId, autoincrement(), primary_key()),
                make_column("first_name", &User::firstName),
                make_column("last_name", &User::lastName),
                make_column("birth_date", &User::birthDate),
                make_column("image_url", &User::imageUrl),
                make_column("type_id", &User::typeId)),
            make_table("user_types",
                make_column("id", &UserType::id, autoincrement(), primary_key()),
                make_column("name", &UserType::name, default_value("name_placeholder"))));

    }

};