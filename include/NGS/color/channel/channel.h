#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class ChannelType> requires ::std::is_object_v<ChannelType>
struct NGS_DLL_API any_channel
{
	using channel_type = ChannelType;
};

template<::std::size_t Count, class ChannelType = byte_<bits::algorithm::bit_to_byte_ceil(Count)>>
	requires ::std::is_arithmetic_v<ChannelType>
struct NGS_DLL_API channel : any_channel<ChannelType>
{
	constexpr static ::std::size_t bit_count() { return Count; }
};

NGS_LIB_MODULE_END
