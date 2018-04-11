#pragma once

#include <string>
#include <vector>

namespace deduction {
	struct function {
		struct parameter {
			parameter() = default;
			parameter(std::string name, std::string type)
				: name { std::move(name) }
				, type { std::move(type) }
			{}

			std::string name;
			std::string type;
		};

		function() = default;
		function(std::string name, std::string fullName, std::vector<parameter> parameters, std::string returnType)
			: name { std::move(name) }
			, full_name { std::move(fullName) }
			, parameters { std::move(parameters) }
			, return_type { std::move(returnType) }
		{};

		std::string name;
		std::string full_name;
		std::vector<parameter> parameters;
		std::string return_type;
	};
}
