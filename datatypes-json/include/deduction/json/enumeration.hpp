//
//  enumeration.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <deduction/datatypes/enumeration.hpp>
#include "json.hpp"

namespace deduction {
	void to_json(nlohmann::json & j, const enumeration::case_label & parameter);
	void from_json(const nlohmann::json & j, enumeration::case_label & parameter);

	void to_json(nlohmann::json & j, const enumeration & function);
	void from_json(const nlohmann::json & j, enumeration & function);
}

