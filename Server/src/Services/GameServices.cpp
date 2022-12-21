#include "../../include/Services/GameServices.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Utils/CrowResponse.hpp"

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

		return CrowResponse::Json(CrowResponse::Code::OK, "", crow::json::wvalue{json_players});
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
	CROW_ROUTE(app, "/check_game_status")([this]() {
		return CheckGameStatus();
	});
}
