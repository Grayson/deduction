//
//  alias.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "alias.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const NameLabel = "name";
	static char const * const UnderlyingTypeLabel = "underlying_type";
	static char const * const ObjectTypeLabel = "_type";
	char const * const AliasTypeLabel = "alias";


	void to_json(json & j, const alias & alias) {
		j = json {
			{ NameLabel, alias.name },
			{ UnderlyingTypeLabel, alias.underlying_type },
			{ ObjectTypeLabel, AliasTypeLabel },
		};
	}

	void from_json(const json & j, alias & alias) {
		alias.name = j.at(NameLabel).get<std::string>();
		alias.underlying_type = j.at(UnderlyingTypeLabel).get<std::string>();
	}
}
