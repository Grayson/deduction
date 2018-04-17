//
//  variable.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <deduction/datatypes/variable.hpp>
#include "json.hpp"
#include "variable.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const NameLabel = "name";
	static char const * const FullNameLabel = "full_name";
	static char const * const TypeLabel = "type";
	static char const * const TypeWithoutQualifiersLabel = "type_without_qualifiers";
	static char const * const IsMutableLabel = "is_mutable";
	static char const * const IsExternLabel = "is_extern";
	static char const * const ObjectTypeLabel = "_type";
	char const * const VariableTypeValue = "variable";

	void to_json(json & j, const variable & variable) {
		j = json {
			{ NameLabel, variable.name },
			{ FullNameLabel, variable.full_name },
			{ TypeLabel, variable.type },
			{ TypeWithoutQualifiersLabel, variable.type_without_qualifiers },
			{ IsMutableLabel, variable.is_mutable },
			{ IsExternLabel, variable.is_extern },
			{ ObjectTypeLabel, VariableTypeValue },
		};
	}

	void from_json(const json & j, variable & variable) {
		variable.name = j.at(NameLabel).get<std::string>();
		variable.full_name = j.at(FullNameLabel).get<std::string>();
		variable.type = j.at(TypeLabel).get<std::string>();
		variable.type_without_qualifiers = j.at(TypeWithoutQualifiersLabel).get<std::string>();
		variable.is_mutable = j.at(IsMutableLabel).get<bool>();
		variable.is_extern = j.at(IsExternLabel).get<bool>();
	}

}
