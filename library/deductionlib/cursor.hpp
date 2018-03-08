//
//  cursor.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/7/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#include <string>
#include <clang-c/Index.h>
#include "utility.hpp"

namespace deduction {
	class cursor {
	public:
		cursor(CXCursor backing);

		bool is_visible() const;
		bool is_available() const;
		bool is_in_main_file() const;

		bool is_preprocessing();
		bool is_invalid();

		CXCursorKind kind();

		CXType type() const;
		std::string const & type_name();

		std::string const & full_name();
		std::string const & name();

		std::string debug_description();

	private:
		CXCursor _backing;
		stdoptional<std::string> _typeName;
		stdoptional<std::string> _fullName;
		stdoptional<std::string> _name;
		stdoptional<CXCursorKind> _kind;
	};
}
