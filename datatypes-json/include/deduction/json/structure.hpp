//
//  structure.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <deduction/datatypes/structure.hpp>
#include "json.hpp"

namespace deduction {
	extern char const * const StructureTypeValue;

	void to_json(nlohmann::json & j, const structure::field & parameter);
	void from_json(const nlohmann::json & j, structure::field & parameter);

	void to_json(nlohmann::json & j, const structure & function);
	void from_json(const nlohmann::json & j, structure & function);
}

