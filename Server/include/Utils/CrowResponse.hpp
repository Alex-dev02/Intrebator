#include <crow.h>
#include <string>

namespace CrowJsonResponse{
	enum class ResponseCode {
		OK = 200,
		INVALID = 400,
		SERVER_ERR = 500
	};

	crow::json::wvalue Response(ResponseCode code, const std::string& message);
};
