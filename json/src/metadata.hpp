#pragma once

#include <string>
#include "json.hpp"

namespace deduction {
	struct metadata {
		std::string version;
		std::string file;
	};

	void to_json(nlohmann::json & j, const metadata & parameter);
	void from_json(const nlohmann::json & j, metadata & parameter);
}
