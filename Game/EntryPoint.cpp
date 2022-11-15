#include <iostream>
#include <string>
#include "../Logger/Debug.h"

// #include "Database/Entities/User.hpp"
// #include "Database/Database.hpp"

//void DatabaseTest() {
//	User u{ 1, "Alex" };
//	DB::m_storage.sync_schema();
//	auto inserted_id = DB::m_storage.insert(u);
//	auto user = DB::m_storage.get<User>(inserted_id);
//	std::cout << user.GetName();
//
//	std::cout << "Hello world!";
//}

int main() {
	//DatabaseTest()

	Debug::Log("Hello world! Info message test");
	Debug::LogWarning("Hello world! Warning message test");
	Debug::LogError("Hello world! Error message test");

}