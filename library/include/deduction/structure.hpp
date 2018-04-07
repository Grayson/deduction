//
//  structure.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/10/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include "function.hpp"

namespace deduction {
	struct structure {
		struct field {
			field() = default;
			field(std::string name, std::string type, bool isMutable)
				: name { std::move(name) }
				, type { std::move(type) }
				, is_mutable { isMutable }
			{}

			std::string name;
			std::string type;
			bool is_mutable;
		};

		structure() = default;
		structure(std::string name, std::string fullName, std::vector<field> fields, std::vector<function> methods, std::vector<function> constructors)
			: name { std::move(name) }
			, full_name { std::move(fullName) }
			, fields { std::move(fields) }
			, methods { std::move(methods) }
			, constructors { std::move(constructors) }
		{}

		std::string name;
		std::string full_name;
		std::vector<field> fields;
		std::vector<function> methods;
		std::vector<function> constructors;
	};
}
