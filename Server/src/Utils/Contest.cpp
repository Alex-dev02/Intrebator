#include "../../include/Utils/Contest.hpp"
#include "../../include/Entities/Questions/NumericQuestion.hpp"
#include "../../include/Entities/Questions/MultipleAnswerQuestion.hpp"

#include <cmath>

void Contest::SetQuestion(std::shared_ptr<Question> question) {
	m_question = question;
}

void Contest::AddParticipant(std::shared_ptr<Player> player) {
	m_participants.push_back(player);
}

void Contest::SetParticipants(const std::vector<std::shared_ptr<Player>>& players) {
	m_participants = players;
}

void Contest::ClearParticipants() {
	m_participants.clear();
}

void Contest::StartTimer() {
	m_time = time(nullptr);
}

Contest::Answer::Answer()
	: m_player(nullptr),
	m_answering_time_s(0),
	m_answer("")
{}

Contest::Answer::Answer(std::shared_ptr<Player> player, uint16_t answering_time_s, const std::string& answer)
	: m_player(player),
	m_answering_time_s(answering_time_s),
	m_answer(answer)
{}

Contest::Answer::operator crow::json::wvalue() const {
	return crow::json::wvalue{
		{"player", static_cast<crow::json::wvalue>(*m_player.get())},
		{"answer", m_answer}
	};
}

crow::json::wvalue Contest::GetResult(uint32_t player_id) {
	auto answer_it = std::find_if(m_answers.begin(), m_answers.end(), [player_id](const Answer& a) {
		return a.m_player->GetId() == player_id;
		});

	if (answer_it == m_answers.end())
		return crow::json::wvalue{
			{"error"}
	};

	auto numeric_question = std::dynamic_pointer_cast<NumericQuestion>(m_question);

	if (numeric_question)
		return crow::json::wvalue{
			{"question", m_question->GetQuestion()},
			{"player", static_cast<crow::json::wvalue>((*answer_it->m_player.get()))},
			{"answer", answer_it->m_answer},
			{"correct_answer", std::to_string(numeric_question->GetAnswer())}
	};

	auto multiple_answer_question = std::dynamic_pointer_cast<MultipleAnswerQuestion>(m_question);

	if (multiple_answer_question)
		return crow::json::wvalue{
			{"question", m_question->GetQuestion()},
			{"player", static_cast<crow::json::wvalue>((*answer_it->m_player.get()))},
			{"answer", answer_it->m_answer},
			{"correct_answer", multiple_answer_question->GetCorrectAnswer()}
	};

	return crow::json::wvalue{
		{"error"}
	};
}

crow::json::wvalue Contest::GetResults() {
	auto numeric_question = std::dynamic_pointer_cast<NumericQuestion>(m_question);
	auto multiple_answer_question = std::dynamic_pointer_cast<MultipleAnswerQuestion>(m_question);

	std::vector<crow::json::wvalue> json_players;
	for (const auto& answer : m_answers) {
		json_players.push_back(
			crow::json::wvalue{
				{ "player", static_cast<crow::json::wvalue>(*(answer.m_player.get())) },
				{ "answer", answer.m_answer }
			}
		);

	}

	return crow::json::wvalue{
		{"question", m_question->GetQuestion()},
		{"answer", numeric_question ?
			std::to_string(numeric_question->GetAnswer()) : multiple_answer_question->GetCorrectAnswer()},
		{"players", crow::json::wvalue{json_players}}
	};
}

uint8_t Contest::GetAnswersSize() {
	return m_answers.size();
}

uint8_t Contest::GetParticipantsSize() {
	return m_participants.size();
}

void Contest::SubmitAnswer(const std::string& answer, std::shared_ptr<Player> player) {
	m_answers.push_back(Answer(player, m_time - time(nullptr), answer));
}

std::vector<Contest::Answer> Contest::GetAnswers() {
	//if (m_time - time(nullptr) >= 15) // commented because of magic number 15, which must be set in a variable as a standard waiting time to answer the questions
	return m_answers;
	return {};
}

std::shared_ptr<Question> Contest::CurrentQuestion() {
	return m_question;
}

std::vector<Contest::EvaluatedAnswer> Contest::GetEvaluatedAnswers() {
	auto opt_evaluated_answers = GetEvaluatedAnswersForNumericQuestion();
	std::vector<EvaluatedAnswer> evaluated_answers;

	if (!opt_evaluated_answers.has_value())
		evaluated_answers = GetEvaluatedAnswersForMultipleQuestion().value();
	else
		evaluated_answers = opt_evaluated_answers.value();

	if (std::holds_alternative<bool>(evaluated_answers[0].m_is_correct_or_margin_error))
		std::stable_partition(evaluated_answers.begin(), evaluated_answers.end(),
			[](const Contest::EvaluatedAnswer& ans) {
				return std::get<bool>(ans.m_is_correct_or_margin_error) == true;
			});
	else
	std::sort(evaluated_answers.begin(), evaluated_answers.end(),
		[](const Contest::EvaluatedAnswer& first_ans, const Contest::EvaluatedAnswer& second_ans) {
			return std::get<float>(first_ans.m_is_correct_or_margin_error) <=
			std::get<float>(second_ans.m_is_correct_or_margin_error);
		});

	return evaluated_answers;
}

std::optional<std::vector<Contest::EvaluatedAnswer>> Contest::GetEvaluatedAnswersForNumericQuestion() {
	auto numeric_question = std::dynamic_pointer_cast<NumericQuestion>(m_question);

	if (!numeric_question)
		return std::nullopt;

	std::vector<Contest::EvaluatedAnswer> evaluated_answers;

	EvaluatedAnswer evaluated_answer;

	for (const auto& answer : m_answers) {
		evaluated_answer.m_player = answer.m_player;
		evaluated_answer.m_is_correct_or_margin_error =
			GetMarginErrorForAnswer(std::stoi(answer.m_answer), numeric_question->GetAnswer());
		evaluated_answers.push_back(evaluated_answer);
	}

	return evaluated_answers;
}

std::optional<std::vector<Contest::EvaluatedAnswer>> Contest::GetEvaluatedAnswersForMultipleQuestion() {
	auto multiple_answer_question = std::dynamic_pointer_cast<MultipleAnswerQuestion>(m_question);

	if (!multiple_answer_question)
		return std::nullopt;

	std::vector<Contest::EvaluatedAnswer> evaluated_answers;

	EvaluatedAnswer evaluated_answer;

	for (const auto& answer : m_answers) {
		evaluated_answer.m_player = answer.m_player;
		evaluated_answer.m_is_correct_or_margin_error =
			answer.m_answer == multiple_answer_question->GetCorrectAnswer();
		evaluated_answers.push_back(evaluated_answer);
	}

	return evaluated_answers;
}

float Contest::GetMarginErrorForAnswer(int given_answer, int correct_answer) {
	return std::abs(correct_answer - given_answer);
}

const std::vector<std::shared_ptr<Player>>& Contest::GetParticipants() const {
	return m_participants;
}

void Contest::ClearContestData() {
	m_participants.clear();
	m_question = nullptr;
	m_answers.clear();
}

void Contest::SetDisputedCell(uint8_t x, uint8_t y) {
	m_disputed_cell_x_coord = x;
	m_disputed_cell_y_coord = y;
}

uint8_t Contest::GetDisputedCellX() const {
	return m_disputed_cell_x_coord;
}

uint8_t Contest::GetDisputedCellY() const {
	return m_disputed_cell_y_coord;
}

/*
bool UsedPowerup(const Player::Powerups& powerupName){
	if(powerupName == Player::Powerups::FIFTYFIFITY){
		if(Player::GetUsed5050Powerup)
			;// return bad
		else
			;// return good
	}
	else if(powerupName == Player::Powerups::FOURANSWERS){
		if(Player::GetUsed4AnswersPowerup)
			;// return bad
		else
			;// return good
	}
	else if(powerupName == Player::Powerups::CORRECTANSWER){
		if(Player::GetUsedCorrectAnswerPowerup)
			;// return bad
		else
			;// return good
	}
}//TODO: !!!!!!!!!!!!!!!!!!!!!!!!!
*/
