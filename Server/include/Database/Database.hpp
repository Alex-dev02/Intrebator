#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "../Entities/User.hpp"
#include "../Entities/Questions/NumericQuestion.hpp"
#include "../Entities/Questions/MultipleAnswerQuestion.hpp"


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
			),
			make_table("multiple_answer_question",
				make_column("id", &MultipleAnswerQuestion::GetId, &MultipleAnswerQuestion::SetId, autoincrement(), primary_key()),
				make_column("question", &MultipleAnswerQuestion::GetQuestion, &MultipleAnswerQuestion::SetQuestion), 
				make_column("first_answer", &MultipleAnswerQuestion::GetFirstAnswer, &MultipleAnswerQuestion::SetFirstAnswer), 
				make_column("second_answer", &MultipleAnswerQuestion::GetSecondAnswer, &MultipleAnswerQuestion::SetSecondAnswer), 
				make_column("third_answer", &MultipleAnswerQuestion::GetThirdAnswer, &MultipleAnswerQuestion::SetThirdAnswer), 
				make_column("corect_answer", &MultipleAnswerQuestion::GetCorrectAnswer, &MultipleAnswerQuestion::SetCorrectAnswer)));
		return storage;
	}

};
