#include "../../include/Services/GameServices.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Utils/CrowResponse.hpp"

GameServices::GameServices(std::shared_ptr<Database> database, std::shared_ptr<Server> server)
	: m_database(database),
	m_server(server),
	m_game(server->GetGame())
{}

const crow::json::wvalue& GameServices::JoinGame(uint32_t user_id, uint8_t room_size) {
	if (m_server->GameIsRunning())
		CrowResponse::Json(CrowResponse::Code::INVALID, "The game is already running!");
	
	UserServices user_services{ m_database };

	auto user = user_services.GetUserById(user_id);

	if (!user)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid user id!");
	
	m_game->SetRoomSize(room_size);

	std::shared_ptr<Player> player = std::make_shared<Player>(std::move(user));
	
	if (m_game->AddPlayer(player)) {
		const auto& players = m_game->GetPlayers();
		std::vector<crow::json::wvalue> json_players;
		
		for (const auto& p : players) {
			json_players.push_back(p.get());
		}

		return CrowResponse::Json(CrowResponse::Code::OK, "", crow::json::wvalue{json_players});
	}
	
	return CrowResponse::Json(CrowResponse::Code::INVALID, "Room is full!");
}

void GameServices::InitRoutes() {
	auto& app = m_server->GetApp();

	CROW_ROUTE(app, "/join_game/<int>/<int>")([this](std::uint32_t user_id, std::uint8_t room_size) {
		return JoinGame(user_id, room_size);
	});
}
