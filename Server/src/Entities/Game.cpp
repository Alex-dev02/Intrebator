#include "../../include/Entities/Game.hpp"
#include "../../include/Services/QuestionServices.hpp"

#include <algorithm> 
#include <random>
#include <chrono>
#include <thread>

std::string Game::StatusToString(Status status) {
	if (status == Status::WAITING_FOR_PLAYERS)
		return "WAITING_FOR_PLAYERS";
	else if (status == Status::SHOW_MAP)
		return  "SHOW_MAP";
	else if (status == Status::ANSWERING_QUESTION)
		return "ANSWERING_QUESTION";
	else if (status == Status::PICKING_BASE)
		return "WAITING_FOR_PLAYERS";
	else if (status == Status::PICKING_CELLS)
		return "PICKING_CELLS";
	else if (status == Status::DUELLING)
		return "DUELLING";
	else if (status == Status::FINISHED)
		return "FINISHED";
	return "ERROR";
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

void Game::PickFreeCells() {
	auto free_cells = m_map.FreeCells();
	do {

		m_mutex.lock();
		Status::ANSWERING_QUESTION;
		m_mutex.unlock();



	} while (true);
}

void Game::GameLoop() {
	using namespace std::chrono_literals;

	m_mutex.lock();
	m_status = Status::SHOW_MAP;
	m_mutex.unlock();
	std::this_thread::sleep_for(5s);

	// first fase, answering numeric question for picking the base
	m_mutex.lock();
	m_contest.SetQuestion(m_questions.front());
	m_questions.erase(m_questions.begin());
	m_contest.SetParticipants(m_players);
	m_contest.StartTimer();
	m_status = Status::ANSWERING_QUESTION;
	m_mutex.unlock();
	WaitForAnswers(15);

	m_mutex.lock();
	m_status = Status::SHOW_RESULTS;
	m_mutex.unlock();
	std::this_thread::sleep_for(3s);
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
	m_questions = question_services.FetchQuestionForGame(GetNumberOfQuestionsToPrepare());
	SetMap();
	ShuffleRounds();
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

int Game::GetRandomValueFrom0UpUntilN(int n){
	std::random_device rnd;
	std::default_random_engine random{rnd()};
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

//void Game::SubmitContestAnswer(const std::string& answer, std::shared_ptr<Player> player) {
//	m_contest.SubmitAnswer(answer, player);
//}

