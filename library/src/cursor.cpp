//
//  cursor.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/7/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "cursor.hpp"
#include <numeric>
#include <vector>

namespace {
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

	std::string qualify_name(CXCursor cursor) {
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

	std::string const InvalidTypeName { "<invalid>" };
}

namespace deduction {
	cursor::cursor(CXCursor backing)
		: _backing { backing }
	{
	}

	bool cursor::is_visible() const {
		return CXVisibility_Default == clang_getCursorVisibility(_backing);
	}

	bool cursor::is_available() const {
		return CXAvailability_Available == clang_getCursorAvailability(_backing);
	}

	bool cursor::is_in_main_file() const {
		return clang_Location_isFromMainFile(clang_getCursorLocation(_backing));
	}

	bool cursor::is_preprocessing() {
		return clang_isPreprocessing(kind());
	}

	bool cursor::is_invalid() {
		return clang_isInvalid(kind());
	}

	CXCursorKind cursor::kind() {
		return *(_kind ? _kind : _kind = clang_getCursorKind(_backing));
	}

	CXType cursor::type() const {
		return clang_getCursorType(_backing);
	}

	std::string const & cursor::type_name() {
		if (!_typeName)
			_typeName = map(clang_getTypeSpelling(type()));
		return _typeName->empty() ? InvalidTypeName : *_typeName;
	}

	std::string const & cursor::full_name() {
		return *(_fullName ? _fullName : _fullName = qualify_name(_backing));
	}

	std::string const & cursor::name() {
		return *(_name ? _name : _name = map(clang_getCursorSpelling(_backing)));
	}

	language cursor::language() const {
		return map(clang_getCursorLanguage(_backing));
	}

	std::string cursor::debug_description() {
		return "<" + full_name() + " (" + type_name() + ")" + ">";
	}
}
