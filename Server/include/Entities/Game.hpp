#pragma once

#include "Player.hpp"

#include "Questions/MultipleAnswerQuestion.hpp"
#include "Questions/NumericQuestion.hpp"
#include "Map.hpp"

#include <memory>
#include <vector>
#include <random>

class Game {
public:
	Game();
	~Game() = default;

	void Run();

	int GetRandomValueFrom0UpUntilN(int n);

public:
	bool AddPlayer(std::shared_ptr<Player> player);
	void SetRoomSize(uint8_t room_size);
	
	const std::vector<std::shared_ptr<Player>>& GetPlayers() const;
private:
	using Turn = std::shared_ptr<Player>;
	using Round = std::vector<Turn>;

private:
	Map m_map;
	uint8_t m_room_size;

private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<Round> m_rounds;
	std::vector<MultipleAnswerQuestion> m_multi_question;
	std::vector<NumericQuestion> m_numeric_question;
};
