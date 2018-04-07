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
		variable(std::string name, std::string type, std::string typeWithoutQualifiers, bool isMutable, bool isExtern)
			: name { std::move(name) }
			, type { std::move(type) }
			, type_without_qualifiers { std::move(typeWithoutQualifiers) }
			, is_mutable { isMutable }
			, is_extern { isExtern}
		{
		}

		std::string name;
		std::string type;
		std::string type_without_qualifiers;
		bool is_mutable;
		bool is_extern;
	};
}
