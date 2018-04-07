//
//  clang-utility.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/9/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include <clang-c/Index.h>
#include "language.hpp"

namespace deduction::clang_utility {
	std::string map(CXString && string);
	deduction::language map(CXLanguageKind languageKind);

	std::string get_name(CXCursor & cursor);
	std::string get_name(CXType const & type);
	std::string get_name(CXType const && type);
	std::string qualify_name(CXCursor & cursor);
	std::string get_type_name(CXCursor & cursor);

	std::string remove_type_qualifiers(std::string typeString);
}
