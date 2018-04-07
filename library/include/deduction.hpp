//
//  deductionlib.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include "parse-result.hpp"
#include "utility.hpp"

namespace deduction {
	EXPORT extern std::string const & version;

	EXPORT parse_result parse(const std::string & sourcefile);
}
