#include "../../include/Services/UserServices.hpp"


const crow::json::wvalue& UserServices::CrowResponseStatusAndMessage(int status, const std::string& message) {
	return crow::json::wvalue{
		{"status", std::to_string(status)},
		{"message", message}
	};
}

const crow::json::wvalue& UserServices::UserRegister(const crow::request& req) {
	// request type: /user/register?name=joe&password=pass&repeat_password=pass
	using namespace sqlite_orm;
	auto name = req.url_params.get("name");
	// if name doesnt exist return status ```idk``` and message "no user_name field found"


	std::string name2{name};

	auto findUser = m_database->get_all<User>(where(c(&User::GetName) == name2), limit(1));
		// m_database->prepare(select(&User::GetId, where(c(&User::GetName) == (name2))));uy
	if(findUser.size() != 1){
		// if findUser is found return status ```idk``` and message "user already exists"
	}

	// request password
	auto password = req.url_params.get("password");
	if(!password)
		// if password not found return status ```idk``` and message "no password field found"
	
	// function for registering the user

	// return status ```100 or 200 idk``` and message "user succesfully registered"
	return crow::json::wvalue{
		{"status", ""},
		{"message", ""}
	};
}

const crow::json::wvalue& UserServices::UserLogIn(const crow::request& req) {
	using namespace sqlite_orm;
	auto name = req.url_params.get("name");
	if (!name)
		throw std::exception("404");

	auto password = req.url_params.get("password");
	if (!password)
		throw std::exception("404");
	try{
		std::string name_str{ name };
		auto user =
			m_database->get_all<User>(where(c(&User::GetName) == name_str));
		if (user.size() == 1 && password == user.front().GetPassword())
			return CrowResponseStatusAndMessage(0, "Success");
	}
	catch (const std::exception&)
	{}

	return CrowResponseStatusAndMessage(1, "Invalid credentials!");
}

void UserServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();
	// /user/register?name=foo&password=pass&repeat_password=pass
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
		
		try {
			UserLogIn(req);
		}
		catch (const std::exception& e) {
			try{
				return crow::response(std::stoi(e.what()));
			}
			catch (const std::exception&)
			{
				return crow::response(505);
			}
		}
	});

}


UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::unique_ptr<User> UserServices::GetUserById(uint32_t id) {
	return std::move(m_database->get_pointer<User>(id));
}
