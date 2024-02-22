#pragma once

#include "NGS/assert/assert.h"
#include "NGS/mpl/mpl.h"
#include "./defined.h"

NGS_LIB_BEGIN

struct NGS_DLL_API movie
{
	NGS_MPL_ENVIRON_BEGIN(movie);
public:
	using frame_type = ::std::size_t;
	using frame_difference_type = ::std::ptrdiff_t;

	constexpr movie() = default;
	constexpr movie(frame_difference_type total_frames, frame_type current_frame = 0)
		: _current_frame(current_frame)
		, _total_frames(total_frames)
	{}

	constexpr auto total_frames()const noexcept { return _total_frames; }
	constexpr auto current_frame()const noexcept { return _current_frame; }

	constexpr void go_to(frame_type frame)noexcept
	{
		if (!::std::is_constant_evaluated())
			NGS_ASSERT(frame < _total_frames, "out of range");
		_current_frame = frame;
	}

public:
	frame_type _current_frame = 0;
	frame_difference_type _total_frames = 0;
};


NGS_LIB_END