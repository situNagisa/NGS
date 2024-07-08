#pragma once

#include "./level.h"
#include "./printer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct config
{
	level level = level::info;
	bool show_time = false;
	bool show_function = true;
};

template<class Char>
constexpr decltype(auto) log(const config& config, printer<Char> auto&& printer, auto&&... args)
{
	using printer_type = decltype(printer);
	using char_type = Char;


};

NGS_LIB_MODULE_END