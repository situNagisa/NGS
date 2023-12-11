#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

template<class _Left, class _Right>
concept same_as = primary_color<_Left> && primary_color<_Right>
&& channels::same_as<typename traits<_Left>::alpha_type, typename traits<_Right>::alpha_type>
&& channels::same_as<typename traits<_Left>::red_type, typename traits<_Right>::red_type>
&& channels::same_as<typename traits<_Left>::green_type, typename traits<_Right>::green_type>
&& channels::same_as<typename traits<_Left>::blue_type, typename traits<_Right>::blue_type>;

NGS_LIB_MODULE_END