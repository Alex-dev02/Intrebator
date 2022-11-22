#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "../Entities/User.hpp"
#include "../Entities/Question.hpp"



class Database {


    void function() {
        using namespace sqlite_orm;

        auto storage = make_storage("db.sqlite",
            make_table("user",
                make_column("id", &User::GetId, &User::SetId, autoincrement(), primary_key()),
                make_column("name", &User::GetName, &User::SetId, unique())
                ),
            make_table("question",
                make_column("id", &Question::GetId, &Question::SetId, autoincrement(), primary_key()),
                make_column("question", &Question::GetQuestion, &Question::SetQuestion)
                ));
        

    }

};