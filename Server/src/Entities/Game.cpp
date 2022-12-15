#include "../../include/Entities/Game.hpp"

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

void Game::SetRoomSize(uint8_t room_size) {
	if (m_room_size == 0)
		m_room_size = room_size;
}

const std::vector<std::shared_ptr<Player>>& Game::GetPlayers() const {
	return m_players;
}
