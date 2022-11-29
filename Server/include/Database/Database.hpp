#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "../Entities/User.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"

namespace sql = sqlite_orm;

class InitDB {
public:
	InitDB() = default;
	InitDB(const InitDB&) = delete;

	static inline auto CreateStorage(const std::string& filename) {
		auto storage = sql::make_storage(filename,
			sql::make_table("user",
				sql::make_column("id", &User::GetId, &User::SetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("name", &User::GetName, &User::SetName, sql::unique())
			),
			sql::make_table("numeric_question",
				sql::make_column("id", &NumericQuestion::GetId, &NumericQuestion::SetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("question", &NumericQuestion::GetQuestion, &NumericQuestion::SetQuestion),
				sql::make_column("answer", &NumericQuestion::GetAnswer, &NumericQuestion::SetAnswer)
			),
			sql::make_table("multiple_answer_question",
				sql::make_column("id", &MultipleAnswerQuestion::GetId, &MultipleAnswerQuestion::SetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("question", &MultipleAnswerQuestion::GetQuestion, &MultipleAnswerQuestion::SetQuestion),
				sql::make_column("first_answer", &MultipleAnswerQuestion::GetFirstAnswer, &MultipleAnswerQuestion::SetFirstAnswer),
				sql::make_column("second_answer", &MultipleAnswerQuestion::GetSecondAnswer, &MultipleAnswerQuestion::SetSecondAnswer),
				sql::make_column("third_answer", &MultipleAnswerQuestion::GetThirdAnswer, &MultipleAnswerQuestion::SetThirdAnswer),
				sql::make_column("corect_answer", &MultipleAnswerQuestion::GetCorrectAnswer, &MultipleAnswerQuestion::SetCorrectAnswer)));
		
		storage.sync_schema();
		return storage;
	}
};

using Storage = decltype(InitDB::CreateStorage(""));


class Database {
public:
	Database() = default;
	Database(const Database&) = delete;

	static Storage& GetStorage();
	static const std::string& GetDatabaseName();
private:
	static const std::string m_database_name;
	static Storage m_storage;
};
