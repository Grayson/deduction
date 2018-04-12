//
//  function.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <deduction/datatypes/function.hpp>
#include "json.hpp"

namespace deduction {
	extern char const * const FunctionReturnTypeLabel;

	void to_json(nlohmann::json & j, const function::parameter & parameter);
	void from_json(const nlohmann::json & j, function::parameter & parameter);

	void to_json(nlohmann::json & j, const function & function);
	void from_json(const nlohmann::json & j, function & function);
}
