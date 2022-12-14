#include "../../include/Services/GameServices.hpp"

GameServices::GameServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

const crow::json::wvalue& GameServices::CreateGame(uint32_t user_id) {
	return {};
}

void GameServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();

	CROW_ROUTE(app, "/create_game/<int>")([this](std::uint32_t user_id) {
		return CreateGame(user_id);
	});
}
