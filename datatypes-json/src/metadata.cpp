#include "metadata.hpp"

namespace deduction {
	using nlohmann::json;

	static char const * const FileLabel = "file";
	static char const * const VersionLabel = "version";

	void to_json(json & j, const metadata & metadata) {
		j = json {
			{ FileLabel, metadata.file },
			{ VersionLabel, metadata.version },
		};
	}

	void from_json(const json & j, metadata & metadata) {
		metadata.file = j.at(FileLabel).get<std::string>();
		metadata.version = j.at(VersionLabel).get<std::string>();
	}
}
