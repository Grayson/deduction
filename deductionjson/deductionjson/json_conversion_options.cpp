//
//  json_conversion_options.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "json_conversion_options.hpp"

namespace deduction {
	json_conversion_options operator |(json_conversion_options const lhs, json_conversion_options const rhs) {
		return static_cast<json_conversion_options>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
	}

	void operator |= (json_conversion_options & lhs, json_conversion_options const rhs) {
		auto tmp = static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs);
		lhs = static_cast<json_conversion_options>(tmp);
	}

	bool has_option(const json_conversion_options options, const json_conversion_options value) {
		auto haystack = static_cast<unsigned>(options);
		auto needle = static_cast<unsigned>(value);
		return (haystack & needle) != 0;
	}
}
