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

	static char const * const ItemsLabel = "items";
}

namespace deduction {
	std::string convert_parsed_result_to_json(const parse_result result) {
		auto visitor = item_visitor {};
		auto itemsInJsonFormat = std::vector<json> {};
		for (const auto & item : result.items) {
			itemsInJsonFormat.emplace_back(mpark::visit(visitor, item));
		}

		auto j = json {
			{ ItemsLabel, itemsInJsonFormat },
		};
		return j.dump();
	}
}
