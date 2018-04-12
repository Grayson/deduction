#pragma once

#include <deduction/datatypes/parse-result.hpp>
#include "json.hpp"

namespace deduction {
	void to_json(nlohmann::json & j, parse_result const & result);
	void from_json(nlohmann::json const & j, parse_result & result);
}
