#include "../../include/Entities/Game.hpp"
#include "../../include/Services/QuestionServices.hpp"

#include <algorithm> 
#include <random>
#include <chrono>
#include <thread>

std::string Game::StatusToString(Status status) {
	switch (status) {
		case Game::Status::WAITING_FOR_PLAYERS:
			return "WAITING_FOR_PLAYERS";
			break;
		case Game::Status::SHOW_MAP:
			return  "SHOW_MAP";
			break;
		case Game::Status::ANSWERING_QUESTION:
			return "ANSWERING_QUESTION";
			break;
		case Game::Status::SHOW_RESULTS:
			return "SHOW_RESULTS";
			break;
		case Game::Status::PICKING_BASE:
			return "PICKING_BASE";
			break;
		case Game::Status::PICKING_CELLS:
			return "PICKING_CELLS";
			break;
		case Game::Status::DUELLING:
			return "DUELLING";
			break;
		case Game::Status::FINISHED:
			return "FINISHED";
			break;
		default:
			return "ERROR";
			break;
	}
}

Game::Game()
	: m_room_size(0),
	m_available_player_colors(Player::GetAllColors()),
	m_status(Status::WAITING_FOR_PLAYERS)
{}

void Game::WaitForAnswers(uint8_t seconds_to_wait) {
	using namespace std::chrono_literals;

	uint8_t seconds_waited = 0;
	while (true) {
		if (m_contest.GetAnswersSize() == m_contest.GetParticipantsSize() || seconds_waited == seconds_to_wait)
			break;
		std::this_thread::sleep_for(1s);
		seconds_waited++;
	}
}

void Game::ShowResults() {
	using namespace std::chrono_literals;
	m_mutex.lock();
	m_status = Status::SHOW_RESULTS;
	m_mutex.unlock();
	std::this_thread::sleep_for(3s);
}

void Game::PrepareContest(const std::vector<std::shared_ptr<Player>>& players) {
	m_mutex.lock();
	m_contest.SetQuestion(m_questions.front());
	m_questions.erase(m_questions.begin());
	m_contest.SetParticipants(m_players);
	m_contest.StartTimer();
	m_status = Status::ANSWERING_QUESTION;
	m_mutex.unlock();
}


void Game::PickFreeCells() {
	using namespace std::chrono_literals;
		m_mutex.lock();
		m_status = Status::PICKING_CELLS;
		m_mutex.unlock();
		std::this_thread::sleep_for(6s);
}

void Game::PickBase() {
	auto answers = m_contest.GetEvaluatedAnswers();
	m_mutex.lock();
	m_status = Status::PICKING_BASE;
	m_mutex.unlock();

	for (const auto& answer : answers)
		SetActioningPlayer(answer.m_player);
}

void Game::SetActioningPlayer(std::shared_ptr <Player> player) {
	m_mutex.lock();
	m_actioning_player = player;
	m_player_is_actioning = true;
	m_mutex.unlock();
	WaitForActioningPlayer();
}

void Game::WaitForActioningPlayer() {
	using namespace std::chrono_literals;

	uint8_t seconds_to_wait  = 0;
	while (seconds_to_wait != 8) {
		if (!m_player_is_actioning)
			break;
		seconds_to_wait++;
		std::this_thread::sleep_for(1s);
	}
}

void Game::GameLoop() {
	using namespace std::chrono_literals;

	m_mutex.lock();
	m_status = Status::SHOW_MAP;
	m_mutex.unlock();
	std::this_thread::sleep_for(5s);

	// first fase, answering numeric question for picking the base
	PrepareContest(m_players);
	WaitForAnswers(15);
	ShowResults();
	PickBase();

	// save the number of free cells 
	while (m_map.FreeCells() > 0) {
		PrepareContest(m_players);
		PickFreeCells();
		WaitForAnswers(15);
		ShowResults();
	}
	// wait for answers in PickFreeCells, maybe remodel it

}

void Game::Run() {
	InitialiseGame();
	std::thread gl(&Game::GameLoop, this);
	gl.detach();
}

uint16_t Game::GetNumberOfQuestionsToPrepare() {
	uint16_t number_of_questions_to_prepare = 0;
	for (const auto& round : m_rounds) {
		number_of_questions_to_prepare += round.size();
	}

	return number_of_questions_to_prepare;
}

void Game::InitialiseGame() {
	QuestionServices question_services{ m_database };
	SetMap();
	ShuffleRounds();
	m_questions = question_services.FetchQuestionForGame(GetNumberOfQuestionsToPrepare());
	ShuffleQuestions();
}


void Game::SetMap() {
	m_room_size = m_players.size();

	if (m_room_size == 2) {
		m_map = Map(3, 3);
		m_rounds = std::vector<Round>(5, m_players);
	}
	else if (m_room_size == 3) {
		m_map = Map(5, 3);
		m_rounds = std::vector<Round>(4, m_players);
	}
	else if (m_room_size == 4) {
		m_map = Map(6, 4);
		m_rounds = std::vector<Round>(5, m_players);
	}
}

void Game::ShuffleRounds() {
	auto rng = std::default_random_engine{};
	for (auto& round : m_rounds) {
		std::shuffle(round.begin(), round.end(), rng);
	}
}

void Game::ShuffleQuestions() {
	auto rng = std::default_random_engine{};
	std::shuffle(m_questions.begin() + 1, m_questions.end(), rng);
	// .begin + 1 so the first question is a numeric one
}

int Game::GetRandomValueFrom0UpUntilN(int n) {
	std::random_device rnd;
	std::default_random_engine random{ rnd() };
	std::uniform_int_distribution<int> uniform(0, n - 1);
	return uniform(random);
}

bool Game::AddPlayer(std::shared_ptr<Player> player) {
	if (m_players.size() < m_room_size) {
		player->SetColor(GetColorToAssignToPlayer());
		m_players.push_back(player);
		return true;
	}
	return false;
}

bool Game::RemovePlayer(std::shared_ptr<Player> player) {
	// player->SetInactive(); ??
	auto player_to_remove = std::find(m_players.begin(), m_players.end(), player);
	if (player_to_remove != m_players.end()) {
		m_available_player_colors.push_back(player->GetColor());
		m_players.erase(player_to_remove);
		return true;
	}
	return false;
}

void Game::SetRoomSize(uint8_t room_size) {
	if (m_room_size == 0)
		m_room_size = room_size;
}

std::optional<std::shared_ptr<Player>> Game::GetPlayer(uint32_t id) {
	auto player_to_remove = std::find_if(m_players.begin(), m_players.end(), [id](std::shared_ptr<Player> player) {
		return player->GetId() == id;
		});
	if (player_to_remove != m_players.end())
		return { *player_to_remove };
	return { std::nullopt };
}

Game::Status Game::GetStatus() const {
	return m_status;
}

const std::vector<std::shared_ptr<Player>>& Game::GetPlayers() const {
	return m_players;
}

Player::Color Game::GetColorToAssignToPlayer() {
	const auto& color = m_available_player_colors.front();
	m_available_player_colors.erase(m_available_player_colors.begin());
	return color;
}

void Game::SetDatabase(std::shared_ptr<Database> database) {
	m_database = database;
}

void Game::SubmitContestAnswer(const std::string& answer, std::shared_ptr<Player> player) {
	m_contest.SubmitAnswer(answer, player);
}

crow::json::wvalue Game::GetContestResult(uint32_t player_id) {
	return m_contest.GetResult(player_id);
}

crow::json::wvalue Game::GetContestResults() {
	return m_contest.GetResults();
}

bool Game::TryPickCell(uint8_t x, uint8_t y, uint32_t player_id, uint8_t is_base) {
	auto player = std::find_if(m_players.begin(), m_players.end(), [player_id](std::shared_ptr<Player> player) {
		return player->GetId() == player_id;
		});
	if (player != m_players.end())
		return m_map.TryPickCell(x, y, *player, is_base);
	return false;
}

std::shared_ptr<Question> Game::CurrentQuestion() {
	return m_contest.CurrentQuestion();
}

const Map& Game::GetMap() {
	return m_map;
}

const std::vector<std::shared_ptr<Player>>& Game::GetContestingPlayers() const {
	return m_contest.GetParticipants();
}

std::shared_ptr<Player> Game::GetActioningPlayer() {
	return m_actioning_player;
}

void Game::SetActioningPlayerOff() {
	m_player_is_actioning = false;
}
