#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Config.h"
#include "NGS/NGS_STL.h"

NGS_BEGIN

class FilePath {
public:
#if NGS_PLATFORM == NGS_WINDOWS
	static constexpr char SEPARATOR = '\\';
#else
	static constexpr char SEPARATOR = '/';
#endif
public:
	FilePath() = default;
	FilePath(std::string_view file) {
		Open(file);
	}
	FilePath(const std::string& file) {
		Open(file);
	}
	FilePath(const char* file) {
		Open(std::string(file));
	}
	operator std::string()const { return GetFilePath(); }

	void Open(std::string_view file) {
		using std::string_view_literals::operator""sv;
		for (const auto& v : (file | std::views::split("\\"sv))) {
			for (const auto& folder : v | std::views::split("/"sv)) {
#if NGS_COMPILER == NGS_GCC
				std::string f;
				for (const auto& c : folder) {
					f += c;
				}
				_path.push_back(f);
#else
				_path.emplace_back(folder.begin(), folder.end());
#endif
			}
		}
	}
	void Clear() { _path.clear(); }
	void Close() { _path.pop_back(); }
	size_t Size()const { return _path.size(); }
	std::string GetDirectory()const {
		std::string dir;
		std::ranges::for_each(_path | std::views::take(_path.size() - 1), [&](const std::string& folder) {
			dir += folder + SEPARATOR;
			});
		return dir;
	}
	std::string GetFilename()const { return _path.back(); }
	std::string GetFilePath()const { return GetDirectory() + GetFilename(); }
private:

private:
	std::vector<std::string> _path;
};

NGS_END
