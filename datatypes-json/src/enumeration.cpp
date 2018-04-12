//
//  enumeration.cpp
//  deductionjson
//
//  Created by Grayson Hansard on 3/26/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <deduction/datatypes/enumeration.hpp>
#include "json.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const NameLabel = "name";
	static char const * const FullNameLabel = "full_name";
	static char const * const CasesLabel = "cases";
	static char const * const ObjectTypeLabel = "_type";
	static char const * const ObjectTypeValue = "enumeration";

	void to_json(json & j, const enumeration::case_label & label) {
		j = json {
			{ NameLabel, label.name },
			{ FullNameLabel, label.full_name },
			{ ObjectTypeLabel, ObjectTypeValue },
		};
	}

	void from_json(const json & j, enumeration::case_label & label) {
		label.name = j.at(NameLabel).get<std::string>();
		label.full_name = j.at(FullNameLabel).get<std::string>();
	}

	void to_json(json & j, const enumeration & enumeration) {
		j = json {
			{ NameLabel, enumeration.name },
			{ FullNameLabel, enumeration.full_name },
			{ CasesLabel, enumeration.case_labels }
		};
	}

	void from_json(const json & j, enumeration & enumeration) {
		enumeration.name = j.at(NameLabel).get<std::string>();
		enumeration.full_name = j.at(FullNameLabel).get<std::string>();
		enumeration.case_labels = j.at(CasesLabel).get<std::vector<enumeration::case_label>>();
	}
}
