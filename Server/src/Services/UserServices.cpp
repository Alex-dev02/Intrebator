#include "../../include/Services/UserServices.hpp"

//using namespace sqlite_orm;

crow::json::wvalue UserServices::UserRegister(std::unique_ptr<crow::request> req) {
	// request type: /user/register?name=joe&password=pass&repeat_pass=pass
	using namespace sqlite_orm;
	auto name = req->url_params.get("name");
	// to be verified if exists
	std::string name2{name};

	auto findUser =
		m_database->prepare(select(&User::GetId, where(sqlite_orm::c(&User::GetName) != (name2))));
	return crow::json::wvalue{
		{"status", ""},
		{"message", ""}
	};
}

crow::json::wvalue UserServices::UserLogIn(std::unique_ptr<crow::request> req) {

}

void UserServices::InitRoutes(std::shared_ptr<Server> server) {
	auto& app = server->GetApp();
	// /user/register?name=foo&password=pass&repeat_password=pass
	CROW_ROUTE(app, "/user/register")
		([this](crow::request& req){
	try{
		UserRegister(std::make_unique<crow::request>(std::move(req)));
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

	CROW_ROUTE(app, "/user/register");

}


UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::unique_ptr<User> UserServices::GetUserById(uint32_t id) {
	return std::move(m_database->get_pointer<User>(id));
}
