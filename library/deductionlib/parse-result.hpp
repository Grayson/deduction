//
//  parse-result.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/9/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <vector>
#include "variant.hpp"
#include "enumeration.hpp"

namespace deduction {
	struct parse_result {
		using item_type = mpark::variant<enumeration>;
		parse_result() = default;
		parse_result(std::vector<item_type> items)
			: items { std::move(items) }
		{}

		std::vector<item_type> items;
	};
}
