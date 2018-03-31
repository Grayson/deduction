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
		variable(std::string name, std::string type, bool isMutable, bool isExtern)
			: name { std::move(name) }
			, type { std::move(type) }
			, is_mutable { isMutable }
			, is_extern { isExtern} 
		{
		}

		std::string name;
		std::string type;
		bool is_mutable;
		bool is_extern;
	};
}
