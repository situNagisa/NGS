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

	void Open(std::string_view path) {
		OpenDirectory(path);
		_filename = _dir.back();
		_dir.pop_back();
	}
	void OpenDirectory(std::string_view dir) {
		using std::string_view_literals::operator""sv;
		for (const auto& v : (dir | std::views::split("\\"sv))) {
			for (const auto& folder : v | std::views::split("/"sv)) {
#if NGS_COMPILER == NGS_GCC
				std::string f;
				for (const auto& c : folder) {
					f += c;
				}
				_dir.push_back(f);
#else
				_dir.emplace_back(folder.begin(), folder.end());
#endif
			}
		}
	}
	void Clear() {
		_filename.clear();
		_dir.clear();
	}
	void Close() { _dir.pop_back(); }
	size_t Size()const { return _dir.size(); }
	std::string GetDirectory()const {
		std::string dir;
		std::ranges::for_each(_dir, [&](const std::string& folder) {
			dir += folder + SEPARATOR;
			});
		return dir;
	}
	std::string GetFilename()const { return _filename; }
	std::string GetFilePath()const { return GetDirectory() + GetFilename(); }
private:

private:
	std::string _filename = {};
	std::vector<std::string> _dir;
};

NGS_END
