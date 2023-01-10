#include "../../include/Services/UserServices.hpp"
#include "../../include/Utils/CrowResponse.hpp"
#include "../../../Logger/Debug.hpp"

std::unique_ptr<User> UserServices::GetUserByName(const std::string& name) {
	using namespace sqlite_orm;
	for (auto& user : m_database->iterate<User>()) {
		if (user.GetName() == name)
			return std::make_unique<User>(user);
	}
	return nullptr;
}

std::optional<int> UserServices::SaveUser(const User& user) {
	try {
		return m_database->insert(user);
	}
	catch (const std::exception& e) {
		return std::nullopt;
	}
}

crow::json::wvalue UserServices::UserRegister(const crow::request& req) {
	// request type: /user/register?name=joe&password=pass
	using namespace sqlite_orm;
	auto name = req.url_params.get("name");
	if (!name)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "No name filed provided!");

	// request password
	auto password = req.url_params.get("password");
	if (!password)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "No password filed provided!");

	std::string str_name{ name };
	auto user = GetUserByName(str_name);
	if (user)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "Username already taken");

	std::string str_password{ password };

	auto inserted_user_id = SaveUser(User(str_name, str_password));

	return CrowResponse::Json(CrowResponse::Code::OK, "",
		inserted_user_id.has_value() ? crow::json::wvalue{ {"player_id", inserted_user_id.value()}} : crow::json::wvalue{});
}

crow::json::wvalue UserServices::UserLogin(const crow::request& req) {
	using namespace sqlite_orm;

	auto name = req.url_params.get("name");
	if (!name) {
		return CrowResponse::Json(CrowResponse::Code::INVALID, "No name filed provided!");
	}

	auto password = req.url_params.get("password");
	if (!password)
		return CrowResponse::Json(CrowResponse::Code::INVALID, "No password filed provided!");

	std::string str_name{ name };

	auto user = GetUserByName(str_name);
	if (user && password == user->GetPassword())
		return CrowResponse::Json(CrowResponse::Code::OK, "", crow::json::wvalue{{"player_id", user->GetId()}});

	return CrowResponse::Json(CrowResponse::Code::INVALID, "Invalid credentials!");
}

void UserServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();
	// request type: /user/register?name=foo&password=pass&repeat_password=pass
	CROW_ROUTE(app, "/user/register")([this](const crow::request& req) {
		return UserRegister(req);
		});

	// /user/login?name=foo&password=pass
	CROW_ROUTE(app, "/user/login")([this](const crow::request& req) {
		return UserLogin(req);
		});

}

UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::unique_ptr<User> UserServices::GetUserById(uint32_t id) {
	return std::move(m_database->get_pointer<User>(id));
}
