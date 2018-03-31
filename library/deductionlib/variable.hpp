//
//  variable.h
//  deductionlib
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>

namespace deduction {
	struct variable {
		variable() = default;
		variable(std::string name, std::string type, bool isMutable)
			: name { std::move(name) }
			, type { std::move(type) }
			, is_mutable { isMutable }
		{
		}

		std::string name;
		std::string type;
		bool is_mutable;
	};
}
