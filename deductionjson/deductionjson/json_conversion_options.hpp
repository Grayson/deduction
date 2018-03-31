//
//  json_conversion_options.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

namespace deduction {
	enum class json_conversion_options : unsigned {
		none = 0,
		pretty_print = 1 << 1,
		include_file_info = 1 << 2,
	};

	json_conversion_options operator |(json_conversion_options const lhs, json_conversion_options const rhs);
	bool has_option(const json_conversion_options options, const json_conversion_options value);
}

