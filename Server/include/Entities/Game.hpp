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
	enum class Status {
		WAITING_FOR_PLAYERS,
		PICKING_BASE,
		PICKING_CELLS,
		DUELLING,
		FINISHED
	};
	static const std::string& StatusToString(Status status);
public:
	Game();
	Game(const Game&) = delete;
	~Game() = default;

	void Run();

	int GetRandomValueFrom0UpUntilN(int n);

public:
	bool AddPlayer(std::shared_ptr<Player> player);
	bool RemovePlayer(std::shared_ptr<Player> player);
	std::optional<std::shared_ptr<Player>> GetPlayer(uint32_t id);
	const std::vector<std::shared_ptr<Player>>& GetPlayers() const;

	Status GetStatus() const;
	void SetRoomSize(uint8_t room_size);



private:
	Player::Color GetColorToAssignToPlayer();
	void InitialiseGame();
	void SetMap();
private:
	using Turn = std::shared_ptr<Player>;
	using Round = std::vector<Turn>;

private:
	Map m_map;

	uint8_t m_room_size;
	Status m_status;
private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<Round> m_rounds;
	std::vector<MultipleAnswerQuestion> m_multi_question;
	std::vector<NumericQuestion> m_numeric_question;
	std::vector<Player::Color> m_available_player_colors;
};
