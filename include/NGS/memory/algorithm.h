#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

void write(auto&& source, void* destination)
{
	::std::memcpy(destination, &source, sizeof(decltype(source)));
}

void read(auto& destination, const void* source)
{
	::std::memcpy(&destination, source, sizeof(decltype(destination)));
}

NGS_LIB_END