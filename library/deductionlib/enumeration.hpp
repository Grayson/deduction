//
//  enumeration.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/9/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

namespace deduction {
	struct enumeration {
		struct case_label {
			case_label() = default;
			case_label(std::string name, std::string fullName)
				: name { std::move(name) }
				, full_name { std::move(fullName) }
			{}

			std::string name;
			std::string full_name;
		};

		enumeration() = default;
		enumeration(std::string name, std::string fullName, std::vector<case_label> caseLabels)
			: name { std::move(name) }
			, full_name { std::move(fullName) }
			, case_labels { std::move(caseLabels) }
		{}

		std::string name;
		std::string full_name;
		std::vector<case_label> case_labels;
	};
}
