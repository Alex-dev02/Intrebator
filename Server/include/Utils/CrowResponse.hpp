#include <crow.h>
#include <string>

class Response {
public:
	enum class Code {
		OK = 200,
		INVALID = 400,
		SERVER_ERROR = 500
	};
		
	static const std::string& ToString(Code code);
	static const crow::json::wvalue& Json(Code code, const std::string& message, const crow::json::wvalue& data);

};
