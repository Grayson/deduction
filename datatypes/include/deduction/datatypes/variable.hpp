#pragma once

#include <string>

namespace deduction {
	struct variable {
		variable() = default;
		variable(std::string name, std::string fullName, std::string type, std::string typeWithoutQualifiers, bool isMutable, bool isExtern)
			: name { std::move(name) }
			, full_name { std::move(fullName) }
			, type { std::move(type) }
			, type_without_qualifiers { std::move(typeWithoutQualifiers) }
			, is_mutable { isMutable }
			, is_extern { isExtern}
		{
		}

		std::string name;
		std::string full_name;
		std::string type;
		std::string type_without_qualifiers;
		bool is_mutable;
		bool is_extern;
	};
}
