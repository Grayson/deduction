//
//  clang-utility.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/9/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "clang-utility.hpp"
#include <numeric>
#include <vector>

namespace deduction::clang_utility {
	std::string map(CXString && string) {
		auto tmp = std::string { clang_getCString(string) };
		clang_disposeString(string);
		return tmp;
	}

	deduction::language map(CXLanguageKind languageKind) {
		switch (languageKind) {
			case CXLanguage_C:
				return deduction::language::c;
			case CXLanguage_ObjC:
				return deduction::language::objc;
			case CXLanguage_CPlusPlus:
				return deduction::language::cpp;
			default:
				return deduction::language::invalid;
		}
	}

	std::string get_name(CXCursor & cursor) {
		return map(clang_getCursorSpelling(cursor));
	}

	std::string get_name(CXType const & type) {
		return map(clang_getTypeSpelling(type));
	}

	std::string get_name(CXType const && type) {
		return get_name(type);
	}

	std::string qualify_name(CXCursor & cursor) {
		auto canContinue = [](CXCursor const & tmp) {
			auto kind = clang_getCursorKind(tmp);
			return !clang_Cursor_isNull(tmp)
			&& !clang_isInvalid(kind)
			&& kind != CXCursor_TranslationUnit;
		};

		auto components = std::vector<std::string> {};
		while(canContinue(cursor)) {
			components.emplace_back(map(clang_getCursorSpelling(cursor)));
			cursor = clang_getCursorSemanticParent(cursor);
		}

		auto begin = components.begin();
		auto seed = *begin;
		begin++;
		std::string name = std::accumulate(begin, components.end(), seed, [](auto const & accumulated, auto const & next) {
			return next + "::" + accumulated;
		});
		return name;
	}

	std::string get_type_name(CXCursor & cursor) {
		return get_name(clang_getCursorType(cursor));
	}

	std::string remove_type_qualifiers(std::string typeString) {
		auto strip = [&](const std::string & needle) {
			auto position = typeString.find(needle);
			if (position == std::string::npos)
				return false;

			typeString.erase(position, needle.length());
			return true;
		};

		while(strip("const") || strip("violatile"))
			; /* Strip keywords */

		while(strip("  "))
			; /* Strip out any double-spaces */

		if (*std::begin(typeString) == ' ')
			typeString.erase(std::begin(typeString));

		if (typeString.size() != 0)
		{
			auto const iter = std::prev(std::end(typeString));
			if (*iter == ' ')
				typeString.erase(iter);
		}

		return typeString;
	}
}
