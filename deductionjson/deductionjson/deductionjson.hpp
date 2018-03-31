//
//  deductionjson.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/26/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include <deduction/deductionlib.hpp>

namespace deduction {
	std::string convert_parsed_result_to_json(const parse_result result);
}
