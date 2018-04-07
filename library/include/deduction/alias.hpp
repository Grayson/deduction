//
//  alias.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/12/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>

namespace deduction {
	struct alias {
		alias() = default;
		alias(std::string name, std::string underlyingType)
			: name { std::move(name) }
			, underlying_type { std::move(underlyingType) }
		{}

		std::string name;
		std::string underlying_type;
	};
}
