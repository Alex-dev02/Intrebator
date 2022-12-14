#include "../../include/Services/UserServices.hpp"

#include <sstream>

std::unique_ptr<User> UserServices::GetUserByName(const std::string& name){
	using namespace sqlite_orm;
	for(auto& user : m_database->iterate<User>()){
		if(user.GetName() == name)
			return std::make_unique<User>(user);
	}

	return nullptr;
}

const crow::json::wvalue& UserServices::CrowResponseStatusAndMessage(int status, const std::string& message) {
	return crow::json::wvalue{
		{"status", status},
		{"message", message}
	};
}

std::optional<int> UserServices::SaveUser(const User& user){
	try{
		return m_database->insert(user);
	}
	catch(const std::exception& e){
		return std::nullopt;
	}
}

const crow::json::wvalue& UserServices::UserRegister(const crow::request& req) {
	// request type: /user/register?name=joe&password=pass&repeat_password=pass
	using namespace sqlite_orm;
	auto name = req.url_params.get("name");
	if(!name)
		throw std::exception("404");
	std::string str_name{name};

	auto findUser = GetUserByName(str_name);
	if(findUser)
		throw std::exception("404");    // change error code accordingly

	// request password
	auto password = req.url_params.get("password");
	if(!password)
		throw std::exception("404");
	std::string str_password{password};
	
	SaveUser(User(str_name, str_password));

	const auto& res = CrowResponseStatusAndMessage(0, "Success");
	return res;
}

const crow::json::wvalue& UserServices::UserLogin(const crow::request& req) {
	using namespace sqlite_orm;
	auto name = req.url_params.get("name");
	if (!name)
		throw std::exception("404");

	auto password = req.url_params.get("password");
	if (!password)
		throw std::exception("404");
	try{
		std::string str_name{ name };
		auto user = GetUserByName(str_name);
		if (user && password == user->GetPassword())
			return CrowResponseStatusAndMessage(0, "Success");
	}
	catch (const std::exception&)
	{}

	return CrowResponseStatusAndMessage(1, "Invalid credentials!");
}

void UserServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();
	// request type: /user/register?name=foo&password=pass&repeat_password=pass
	CROW_ROUTE(app, "/user/register")([this](const crow::request& req){
		try{
			UserRegister(req);
		}
		catch(const std::exception& e) {
			try {
				return crow::response(std::stoi(e.what()));
			}
			catch (const std::exception&){
				return crow::response(505); // internal server error
			}
		}
	});

	// /user/login?name=foo&password=pass
	CROW_ROUTE(app, "/user/login")([this](const crow::request& req) {
		std::ostringstream os;
		try {
			return UserLogin(req);
		}
		catch (const std::exception& e) {
			return crow::json::wvalue({ e.what()});
		}
	});

}


UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::unique_ptr<User> UserServices::GetUserById(uint32_t id) {
	return std::move(m_database->get_pointer<User>(id));
}
