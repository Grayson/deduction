//
//  deductionlib.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include "utility.hpp"
#include <string>

namespace deduction {
	EXPORT extern std::string const & version;

	EXPORT bool test();

	EXPORT bool parse(const std::string & sourcefile);
}
