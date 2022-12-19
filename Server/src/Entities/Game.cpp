#include "../../include/Entities/Game.hpp"

#include <algorithm> 

const std::string& Game::StatusToString(Status status) {
	if (status == Status::WAITING_FOR_PLAYERS)
		return "WAITING_FOR_PLAYERS";
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


void Game::Run() {
	InitialiseGame();
}

void Game::InitialiseGame() {
	SetMap();

}

void Game::SetMap() {
	m_room_size = m_players.size();

	if (m_room_size == 2)
		m_map = Map(3, 3);
	else if (m_room_size == 3)
		m_map = Map(5, 3);
	else if (m_room_size == 4)
		m_map = Map(6, 4);

	m_rounds.resize(m_players.size() * 2);

	for (auto& round : m_rounds) {
		round.resize(m_players.size());
		for (auto& turn : round) {
			turn = m_players[rand() % m_players.size()];
		}
	} // probabil trebuie putin revizuita alocarea rundelor etc, nush acum
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
