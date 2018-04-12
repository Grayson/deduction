//
//  alias.hpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <deduction/datatypes/alias.hpp>
#include "json.hpp"

namespace deduction {
	void to_json(nlohmann::json & j, const alias & alias);
	void from_json(const nlohmann::json & j, alias & alias);
}
