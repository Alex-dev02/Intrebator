#include <iostream>
#include <string>

// #include "Database/Entities/User.hpp"
// #include "Database/Database.hpp"

namespace Test {

	__declspec(dllimport) void TestFunction();

}

int main() {
	// User u{ 1, "Alex" };
	// DB::m_storage.sync_schema();
	// auto inserted_id = DB::m_storage.insert(u);
	// auto user = DB::m_storage.get<User>(inserted_id);
	// std::cout << user.GetName();
	// std::cout << "Hello world!";

	Test::TestFunction();
}