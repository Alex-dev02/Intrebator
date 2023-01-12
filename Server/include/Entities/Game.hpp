#pragma once
#define fur_lop for

#include "Player.hpp"

#include "Questions/MultipleAnswerQuestion.hpp"
#include "Questions/NumericQuestion.hpp"
#include "Map.hpp"
#include "../Utils/Contest.hpp"
#include "../Database/Database.hpp"

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
	const std::vector<std::shared_ptr<Player>>& GetContestingPlayers() const;

	Status GetStatus() const;
	void SetRoomSize(uint8_t room_size);
	void SetDatabase(std::shared_ptr<Database> database);

public:
	void SubmitContestAnswer(const std::string& answer, std::shared_ptr<Player> player);
	crow::json::wvalue GetContestResult(uint32_t player_id);
	crow::json::wvalue GetContestResults();
	bool TryPickCell(uint8_t x, uint8_t y, uint32_t player_id, uint8_t is_base);
	std::shared_ptr<Question> CurrentQuestion();
	const Map& GetMap();
	std::shared_ptr<Player> GetActioningPlayer();
	void SetActioningPlayerOff();

private:
	Player::Color GetColorToAssignToPlayer();
	void InitialiseGame();
	void SetMap();
	void ShuffleRounds();
	void ShuffleQuestions();
	uint16_t GetNumberOfQuestionsToPrepare();
	// threading
private:
	void GameLoop();
	void WaitForAnswers(uint8_t seconds_to_wait);
	void PickFreeCells();
	void ShowResults();
	void PrepareContest(const std::vector<std::shared_ptr<Player>>& players);
	void PickBase();
	void SetActioningPlayer(std::shared_ptr <Player> player);
	void WaitForActioningPlayer();

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
	std::vector<std::shared_ptr<Question>> m_questions;
	std::vector<Player::Color> m_available_player_colors;
	
	std::shared_ptr<Player> m_actioning_player;
	bool m_player_is_actioning = false;

private:
	std::shared_ptr<Database> m_database;
};
