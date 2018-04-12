//
//  deductionlib.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include "utility.hpp"
#include <deduction/datatypes/parse-result.hpp>

namespace deduction {
	EXPORT extern std::string const & version;

	EXPORT parse_result parse(const std::string & sourcefile);
}
