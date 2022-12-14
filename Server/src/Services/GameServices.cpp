#include "../../include/Services/GameServices.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Utils/CrowResponse.hpp"

GameServices::GameServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

const std::pair<bool, const crow::json::wvalue&>& GameServices::CreateGame(uint32_t user_id) {
	UserServices user_services{ m_database };

	auto user = user_services.GetUserById(user_id);

	if (!user)
		return {false, CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid user id!")};
	return { true, CrowResponse::Json(CrowResponse::Code::OK) };
}

void GameServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();

	CROW_ROUTE(app, "/create_game/<int>")([this, server](std::uint32_t user_id) {
		const auto& res = CreateGame(user_id);
		if (res.first)
			server->StartGame();
		return res.second;
	});
}
