#pragma once

#include <cpr/cpr.h>

#include "../../Logger/Debug.hpp"

static class Network {
public:
	Network() {
		cpr::Response r = cpr::Get(cpr::Url{ "https://api.github.com/repos/whoshuu/cpr/contributors" },
			cpr::Authentication{ "user", "pass", cpr::AuthMode::BASIC },
			cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
		Debug::Log(r.status_code);
		Debug::Log(r.header["content-type"]);
		Debug::Log(r.text);
	}

private:
};
