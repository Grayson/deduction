//
//  function.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "function.hpp"

#include <algorithm>
#include <vector>
#include <deduction/datatypes/function.hpp>
#include "json.hpp"

namespace deduction {
	using nlohmann::json;

	char const * const FunctionReturnTypeLabel = "return_type";

	static char const * const NameLabel = "name";
	static char const * const FullNameLabel = "full_name";
	static char const * const ParametersLabel = "parameters";
	static char const * const TypeLabel = "type";
	static char const * const ObjectTypeLabel = "_type";
	char const * const FunctionTypeValue = "function";

	void to_json(json & j, const function::parameter & parameter) {
		j = json {
			{ NameLabel, parameter.name },
			{ TypeLabel, parameter.type },
		};
	}

	void from_json(const json & j, function::parameter & parameter) {
		parameter.name = j.at(NameLabel).get<std::string>();
		parameter.type = j.at(TypeLabel).get<std::string>();
	}

	void to_json(json & j, const function & function) {
		j = json {
			{ NameLabel, function.name },
			{ FullNameLabel, function.full_name },
			{ ParametersLabel, function.parameters },
			{ FunctionReturnTypeLabel, function.return_type },
			{ ObjectTypeLabel, FunctionTypeValue },
		};
	}

	void from_json(const json & j, function & function) {
		function.name = j.at(NameLabel).get<std::string>();
		function.full_name = j.at(FullNameLabel).get<std::string>();
		function.parameters = j.at(ParametersLabel).get<std::vector<function::parameter>>();
		function.return_type = j.at(FunctionReturnTypeLabel).get<std::string>();
	}
}
