#pragma once

#include "NGS/nsl/depend.h"
#include "NGS/nsl/io/MultiplexIO.h"
#include "NGS/nsl/file/File.h"

//”√”⁄≤‚ ‘

NSL_BEGIN

NGS_HPP_INLINE int MultIO::Poll(int timeout) {
	using p = pollfd;
	std::vector<p> polls = {};
	for (auto& i : _files) {
		auto [file, event, revents] = i;
		polls.emplace_back(file->_fd, ngs::int16(event), ngs::int16(revents));
	}
	int ret = poll(polls.data(), polls.size(), timeout);
	for (size_t i = 0; i < polls.size(); i++)
	{
		auto [file, event, revents] = _files.at(i);
		revents = polls.at(i).revents;
	}
	return ret;
}

NSL_END