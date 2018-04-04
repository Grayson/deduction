//
//  structure.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "structure.hpp"

#include <algorithm>
#include <vector>
#include <deduction/structure.hpp>
#include "json.hpp"
#include "function.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const NameLabel = "name";
	static char const * const FullNameLabel = "full_name";
	static char const * const FieldsLabel = "fields";
	static char const * const MethodsLabel = "methods";
	static char const * const TypeLabel = "type";
	static char const * const IsMutableLabel = "is_mutable";
	static char const * const ObjectTypeLabel = "_type";
	static char const * const ObjectTypeValue = "struct";

	void to_json(json & j, const structure::field & field) {
		j = json {
			{ NameLabel, field.name },
			{ TypeLabel, field.type },
			{ IsMutableLabel, field.is_mutable },
		};
	}

	void from_json(const json & j, structure::field & field) {
		field.name = j.at(NameLabel).get<std::string>();
		field.type = j.at(TypeLabel).get<std::string>();
		field.is_mutable = j.at(IsMutableLabel).get<bool>();
	}

	void to_json(json & j, const deduction::structure & structure) {
		j = json {
			{ NameLabel, structure.name },
			{ FullNameLabel, structure.full_name },
			{ FieldsLabel, structure.fields },
			{ MethodsLabel, structure.methods },
			{ ObjectTypeLabel, ObjectTypeValue },
		};
	}

	void from_json(const json & j, deduction::structure & structure) {
		structure.name = j.at(NameLabel).get<std::string>();
		structure.full_name = j.at(FullNameLabel).get<std::string>();
		structure.fields = j.at(FieldsLabel).get<std::vector<structure::field>>();
		structure.methods = j.at(MethodsLabel).get<std::vector<function>>();
	}
}
