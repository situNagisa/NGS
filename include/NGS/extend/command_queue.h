#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

class NGS_API  CommandQueue {
public:
	using element_type = std::function<void()>;

public:

	void AddCommand(const element_type& command) { _commands.push(command); }

	void Run() {
		while (!_commands.empty()) {
			_commands.front()();
			_commands.pop();
		}
	}
private:
	std::queue<element_type> _commands{};
};

NGS_END
