//
//  variable.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <deduction/variable.hpp>
#include "json.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const NameLabel = "name";
	static char const * const TypeLabel = "type";
	static char const * const TypeWithoutQualifiersLabel = "type_without_qualifiers";
	static char const * const IsMutableLabel = "is_mutable";
	static char const * const IsExternLabel = "is_extern";

	void to_json(json & j, const variable & variable) {
		j = json {
			{ NameLabel, variable.name },
			{ TypeLabel, variable.type },
			{ TypeWithoutQualifiersLabel, variable.type_without_qualifiers },
			{ IsMutableLabel, variable.is_mutable },
			{ IsExternLabel, variable.is_extern },
		};
	}

	void from_json(const json & j, variable & variable) {
		variable.name = j.at(NameLabel).get<std::string>();
		variable.type = j.at(TypeLabel).get<std::string>();
		variable.type_without_qualifiers = j.at(TypeWithoutQualifiersLabel).get<std::string>();
		variable.is_mutable = j.at(IsMutableLabel).get<bool>();
		variable.is_extern = j.at(IsExternLabel).get<bool>();
	}

}
