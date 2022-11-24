#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "../Entities/User.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"



class Database {

	auto function() {
		using namespace sqlite_orm;

		auto storage = make_storage("db.sqlite",
			make_table("user",
				make_column("id", &User::GetId, &User::SetId, autoincrement(), primary_key()),
				make_column("name", &User::GetName, &User::SetName, unique())
			),
			make_table("numeric_question",
				make_column("id", &NumericQuestion::GetId, &NumericQuestion::SetId, autoincrement(), primary_key()),
				make_column("question", &NumericQuestion::GetQuestion, &NumericQuestion::SetQuestion),
				make_column("answer", &NumericQuestion::GetAnswer, &NumericQuestion::SetAnswer)
			));
		return storage;
	}

};
