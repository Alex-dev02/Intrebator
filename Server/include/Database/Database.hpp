#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "../Entities/User.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"
#include "../Entities/Match.hpp"

namespace sql = sqlite_orm;

namespace InitDB{
	inline auto CreateStorage(const std::string& filename) {
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
				sql::make_column("corect_answer", &MultipleAnswerQuestion::GetCorrectAnswer, &MultipleAnswerQuestion::SetCorrectAnswer)
			)/*,
			sql::make_table("match",
				sql::make_column("id", &Match::GetId, &Match::SetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("date", &Match::GetDate, &Match::SetDate)
			)*/
			// user_match table with foreign keys to user's name (and maybe id), the match id (and probably the date), and the score from the player
		);
		
		storage.sync_schema();
		return storage;
	}
};

class Database {
public:
	using Storage = decltype(InitDB::CreateStorage(""));
public:
	Database(const std::string& database_name)
		: m_database_name(database_name),
		m_storage(InitDB::CreateStorage(m_database_name))
	{}
	Database(const Database&) = delete;

	Storage& GetStorage() {
		return m_storage;
	}
	const std::string& GetDatabaseName() {
		return m_database_name;
	}

private:
	const std::string m_database_name;
	Storage m_storage;
};
