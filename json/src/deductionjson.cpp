//
//  deductionjson.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/26/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "deductionjson.hpp"
#include <vector>

#include <deduction/datatypes/alias.hpp>
#include <deduction/datatypes/function.hpp>
#include <deduction/datatypes/enumeration.hpp>
#include <deduction/datatypes/structure.hpp>
#include <deduction/datatypes/variable.hpp>
#include <deduction/datatypes/variant.hpp>
#include <deduction/json/alias.hpp>
#include <deduction/json/enumeration.hpp>
#include <deduction/json/function.hpp>
#include <deduction/json/parse-result.hpp>
#include <deduction/json/structure.hpp>
#include <deduction/json/variable.hpp>
#include <deduction/json/json.hpp>
#include <deduction/json/metadata.hpp>

namespace {
	static char const * const ItemsLabel = "items";
	static char const * const MetadataLabel = "metadata";
}

namespace deduction {
	using nlohmann::json;

	std::string convert_parsed_result_to_json(const parse_result & result) {
		auto j = json {
			{ ItemsLabel, result },
		};
		return j.dump();
	}

	std::string convert_header_to_json(const std::string & headerPath, json_conversion_options const options) {
		auto const result = parse(headerPath);
		auto j = json {
			{ MetadataLabel, metadata { deduction::version, headerPath } },
			{ ItemsLabel, result },
		};

		auto const tabSize = has_option(options, json_conversion_options::pretty_print) ? 4 : 0;
		return j.dump(tabSize);
	}
}
