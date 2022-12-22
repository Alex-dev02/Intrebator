#pragma once
#define fur_lop for      // <:

#include "Player.hpp"

#include "Questions/MultipleAnswerQuestion.hpp"
#include "Questions/NumericQuestion.hpp"
#include "Map.hpp"
#include "../Utils/Contest.hpp"

#include <mutex>
#include <memory>
#include <vector>
#include <random>

class Game {
public:
	enum class Status {
		WAITING_FOR_PLAYERS,
		SHOW_MAP,
		ANSWERING_QUESTION,
		SHOW_RESULTS,
		PICKING_BASE,
		PICKING_CELLS,
		DUELLING,
		FINISHED
	};

	std::string StatusToString(Status status);
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
	void ShuffleRounds();

	// threading
private:
	void GameLoop();
	void WaitForAnswers(uint8_t seconds_to_wait);

private:
	std::mutex m_mutex;

private:
	using Turn = std::shared_ptr<Player>;
	using Round = std::vector<Turn>;

private:
	Map m_map;
	Contest m_contest;

	uint8_t m_room_size;
	Status m_status;
private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<Round> m_rounds;
	std::vector<std::unique_ptr<Question>> m_questions;
	std::vector<Player::Color> m_available_player_colors;
};
