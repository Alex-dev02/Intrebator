#include "../../include/Entities/Game.hpp"

#include <algorithm> 

Game::Game()
	: m_map(Map(5,3)),
	m_room_size(0)
{
	/*m_rounds.resize(m_players.size() * 2);

	for (auto& round : m_rounds) {
		round.resize(m_players.size());
		for (auto& turn : round) {
			turn = std::make_unique<Player>(m_players[rand() % m_players.size()]);
		}
	}*/ // trebuie facuta asta abia cand au intrat toti playerii si s a dat start joc
}


void Game::Run() {
	for (auto& round : m_rounds) {
		for (auto& turn : round) {

		}
	}
}


int Game::GetRandomValueFrom0UpUntilN(int n){
	std::random_device rnd;
	std::default_random_engine random{rnd()};
	std::uniform_int_distribution<int> uniform(0, n - 1);
	return uniform(random);
}

bool Game::AddPlayer(std::shared_ptr<Player> player) {
	if (m_players.size() < m_room_size) {
		m_players.push_back(player);
		return true;
	}
	return false;
}

void Game::RemovePlayer(std::shared_ptr<Player> player) {
	player->SetInactive();
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

const std::vector<std::shared_ptr<Player>>& Game::GetPlayers() const {
	return m_players;
}
