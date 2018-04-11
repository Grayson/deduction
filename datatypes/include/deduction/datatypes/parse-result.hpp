#pragma once

#include <vector>
#include "alias.hpp"
#include "variant.hpp"
#include "enumeration.hpp"
#include "function.hpp"
#include "structure.hpp"
#include "variable.hpp"

namespace deduction {
	struct parse_result {
		using item_type = mpark::variant<alias, enumeration, function, structure, variable>;
		parse_result() = default;
		parse_result(std::vector<item_type> items)
			: items { std::move(items) }
		{}

		std::vector<item_type> items;
	};
}
