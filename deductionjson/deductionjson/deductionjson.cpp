//
//  deductionjson.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/26/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "deductionjson.hpp"
#include <vector>
#include <deduction/variant.hpp>
#include "json.hpp"

#include "alias.hpp"
#include "enumeration.hpp"
#include "function.hpp"
#include "structure.hpp"
#include "variable.hpp"

namespace {
	using nlohmann::json;

	struct item_visitor {
		json operator()(const deduction::alias & a) const { return a; }
		json operator()(const deduction::enumeration & en) const { return en; }
		json operator()(const deduction::function & fun) const { return fun; }
		json operator()(const deduction::structure & st) const { return st; }
		json operator()(const deduction::variable & var) const { return var; }
	};

	std::vector<json> map(const deduction::parse_result & result) {
		auto visitor = item_visitor {};
		auto itemsInJsonFormat = std::vector<json> {};
		std::transform(std::begin(result.items), std::end(result.items), std::back_inserter(itemsInJsonFormat), [&](const auto & x) { return mpark::visit(visitor, x); });
		return itemsInJsonFormat;
	}

	static char const * const ItemsLabel = "items";
	static char const * const FilePathLabel = "filepath";
}

namespace deduction {
	std::string convert_parsed_result_to_json(const parse_result result) {
		auto j = json {
			{ ItemsLabel, map(result) },
		};
		return j.dump();
	}

	std::string convert_header_to_json(const std::string & headerPath, json_conversion_options const options) {
		auto const result = parse(headerPath);
		auto j = json {
			{ ItemsLabel, map(result) },
		};

		if (has_option(options, json_conversion_options::include_file_info))
			j[FilePathLabel] = headerPath;

		auto const tabSize = has_option(options, json_conversion_options::pretty_print) ? 4 : 0;
		return j.dump(tabSize);
	}
}
