#include "parse-result.hpp"
#include <stdexcept>
#include "alias.hpp"
#include "enumeration.hpp"
#include "function.hpp"
#include "structure.hpp"
#include "variable.hpp"

namespace {
	using nlohmann::json;

	struct item_visitor {
		json operator()(const deduction::alias & a) const { return a; }
		json operator()(const deduction::enumeration & en) const { return en; }
		json operator()(const deduction::function & fun) const { return fun; }
		json operator()(const deduction::structure & st) const { return st; }
		json operator()(const deduction::variable & var) const { return var; }
	};

	std::vector<json> map(const deduction::parse_result & result) {
		auto visitor = item_visitor {};
		auto itemsInJsonFormat = std::vector<json> {};
		std::transform(std::begin(result.items), std::end(result.items), std::back_inserter(itemsInJsonFormat), [&](const auto & x) { return mpark::visit(visitor, x); });
		return itemsInJsonFormat;
	}

	static char const * const TypeLabel = "_type";
}

namespace deduction {
	using nlohmann::json;

	void to_json(json & j, parse_result const & result) {
		j = map(result);
	}

	void from_json(json const & j, parse_result & result) {
		std::transform(std::begin(j), std::end(j), std::back_inserter(result.items), [](json const & obj) {
			auto const type = obj.at(TypeLabel).get<std::string>();
			if (type == AliasTypeLabel) {
				return parse_result::item_type(obj.get<alias>());
			}
			else if (type == EnumerationTypeValue) {
				return parse_result::item_type(obj.get<enumeration>());
			}
			else if (type == FunctionTypeValue) {
				return parse_result::item_type(obj.get<function>());
			}
			else if (type == StructureTypeValue) {
				return parse_result::item_type(obj.get<structure>());
			}
			else if (type == VariableTypeValue) {
				return parse_result::item_type(obj.get<variable>());
			}

			throw std::runtime_error { "Unhandled type: " + type };
		});
	}
}
