#include "../../include/Services/GameServices.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Utils/CrowResponse.hpp"
#include "../../include/Entities/User.hpp"

GameServices::GameServices(std::shared_ptr<Database> database, std::shared_ptr<Server> server)
	: m_database(database),
	m_server(server),
	m_game(server->GetGame()),
	m_user_services(std::make_shared<UserServices>(UserServices(database)))
{}

crow::json::wvalue GameServices::JoinGame(uint32_t user_id, uint8_t room_size) {
	if (m_server->GameIsRunning())
		CrowResponse::Json(CrowResponse::Code::INVALID, "The game is already running!");

	auto user = m_user_services->GetUserById(user_id);

	if (!user)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid user id!");

	m_game->SetRoomSize(room_size);

	std::shared_ptr<Player> player = std::make_shared<Player>(std::move(user));

	if (m_game->AddPlayer(player)) {
		const auto& players = m_game->GetPlayers();
		std::vector<crow::json::wvalue> json_players;

		for (const auto& p : players) {
			json_players.push_back(static_cast<crow::json::wvalue>(*p.get()));
		}

		return CrowResponse::Json(CrowResponse::Code::OK, "", crow::json::wvalue{ json_players });
	}

	return CrowResponse::Json(CrowResponse::Code::INVALID, "Room is full!");
}

crow::json::wvalue GameServices::LeaveGame(uint32_t user_id) {
	auto user = m_user_services->GetUserById(user_id);

	if (!user)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid user id!");

	auto player_to_remove = m_game->GetPlayer(user->GetId());
	if (player_to_remove.has_value() && m_game->RemovePlayer(player_to_remove.value())) {
		return CrowResponse::Json(CrowResponse::Code::OK);
	}
	return CrowResponse::Json(CrowResponse::Code::INVALID, "Player not found!");
}

crow::json::wvalue GameServices::StartGame() {
	m_server->StartGame();
	return CrowResponse::Json(CrowResponse::Code::OK);
}

crow::json::wvalue GameServices::CheckGameStatus() {
	auto status = m_game->StatusToString(m_game->GetStatus());
	return CrowResponse::Json(CrowResponse::Code::OK, status);
}

crow::json::wvalue GameServices::SubmitAnswerForCurrentQuestion(const crow::request& req) {

	auto body = crow::json::load(req.body);

	if (!body)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "No request body found");

	try {
		if (m_game->GetStatus() != Game::Status::ANSWERING_QUESTION)
			return CrowResponse::Json(CrowResponse::Code::INVALID, "Could not submit answer in this fase!");

		auto player = m_game->GetPlayer(body["player_id"].i());

		if (!player.has_value())
			return CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid user");

		m_game->SubmitContestAnswer(body["answer"].s(), player.value());

		return CrowResponse::Json(CrowResponse::Code::OK);
	}
	catch (const std::exception&) {
		return CrowResponse::Json(CrowResponse::Code::SERVER_ERROR);
	}

}

crow::json::wvalue GameServices::GetPoolResults(uint32_t player_id) {
	auto answer = m_game->GetContestResult(player_id);
	
	return CrowResponse::Json(CrowResponse::Code::OK, "", answer);
}

crow::json::wvalue GameServices::TryPickCell(uint8_t x, uint8_t y, uint32_t player_id) {
	// should differentiate what kind of problem caused the invalid response
	return CrowResponse::Json(
		m_game->TryPickCell(x, y, player_id) ? CrowResponse::Code::OK : CrowResponse::Code::INVALID
	);
}

crow::json::wvalue GameServices::GetCurrentQuestion() {
	auto question = m_game->CurrentQuestion();
	auto numeric_question = std::dynamic_pointer_cast<NumericQuestion>(question);
	auto multiple_answer_question = std::dynamic_pointer_cast<MultipleAnswerQuestion>(question);

	if (numeric_question)
		return CrowResponse::Json(CrowResponse::Code::OK, "",
			crow::json::wvalue{
				{"question", numeric_question->GetQuestion()}
			}
	);
	else if (multiple_answer_question)
		return CrowResponse::Json(CrowResponse::Code::OK, "",
			crow::json::wvalue{
				{"question", multiple_answer_question->GetQuestion()},
				{"answers", static_cast<crow::json::wvalue>(*multiple_answer_question.get())}
			}
	);

	return CrowResponse::Json(CrowResponse::Code::SERVER_ERROR);
}

crow::json::wvalue GameServices::GetMap() {
	return CrowResponse::Json(CrowResponse::Code::OK, "", static_cast<crow::json::wvalue>(m_game->GetMap()));
}

crow::json::wvalue GameServices::GetPlayers() {
	const auto& players = m_game->GetPlayers();
	std::vector<crow::json::wvalue> json_players;

	for (const auto& p : players) {
		json_players.push_back(static_cast<crow::json::wvalue>(*p.get()));
	}
	
	return CrowResponse::Json(CrowResponse::Code::OK, "", crow::json::wvalue{ json_players });
}

crow::json::wvalue GameServices::ActivatePowerup(){
	return crow::json::wvalue{};
}

crow::json::wvalue GameServices::GetContestingPlayers() {
	std::vector<crow::json::wvalue> json_players;
	const auto& contesting_players = m_game->GetContestingPlayers();

	for (const auto& player : contesting_players)
		json_players.push_back(static_cast<crow::json::wvalue>(*player.get()));

	return crow::json::wvalue{json_players};
}

void GameServices::InitRoutes() {
	auto& app = m_server->GetApp();

	CROW_ROUTE(app, "/join_game/<int>/<int>")([this](std::uint32_t user_id, std::uint8_t room_size) {
		return JoinGame(user_id, room_size);
		});
	CROW_ROUTE(app, "/leave_game/<int>")([this](std::uint32_t user_id) {
		return LeaveGame(user_id);
		});
	CROW_ROUTE(app, "/start_game")([this]() {
		return StartGame();
		});
	CROW_ROUTE(app, "/game_status")([this]() {
		return CheckGameStatus();
		});
	CROW_ROUTE(app, "/submit_answer_for_current_question").methods("POST"_method) ([this](const crow::request& req) {
		return SubmitAnswerForCurrentQuestion(req);
		});
	CROW_ROUTE(app, "/get_pool_results/<int>")([this](uint32_t player_id) {
		return GetPoolResults(player_id);
		});
	CROW_ROUTE(app, "/pick_cell/<int>/<int>/<int>")([this](uint8_t x, uint8_t y, uint32_t player_id) {
		return TryPickCell(x, y, player_id);
		});
	CROW_ROUTE(app, "/current_question")([this]() {
		return GetCurrentQuestion();
		});
	CROW_ROUTE(app, "/map")([this]() {
		return GetMap();
		});
	CROW_ROUTE(app, "/players")([this]() {
		return GetPlayers();
		});
	CROW_ROUTE(app, "/activate_powerup")([this](){
		return ActivatePowerup();
	});
	CROW_ROUTE(app, "/contesting_players")([this]() {
		return GetContestingPlayers();
	});
}
