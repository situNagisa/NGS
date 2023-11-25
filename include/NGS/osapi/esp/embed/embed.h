#pragma once

#include "./defined.h"

NGS_OS_ESP_EMBED_BEGIN

NGS_OS_ESP_EMBED_END

#define NGS_OS_ESP_EMBED_ID(filename,...) filename##__VA_OPT__(_)##__VA_ARGS__

#define NGS_OS_ESP_EMBED_REGISTER(id,filename,...)																									\
extern const NGS_ byte _##filename##__VA_ARGS__##_start[] asm("_binary_" NGS_PP_TO_STRING(NGS_OS_ESP_EMBED_ID(filename, __VA_ARGS__)) "_start");	\
extern const NGS_ byte _##filename##__VA_ARGS__##_end[] asm("_binary_" NGS_PP_TO_STRING(NGS_OS_ESP_EMBED_ID(filename, __VA_ARGS__)) "_end");		\
inline std::span<const NGS_ byte> id{ _##filename##__VA_ARGS__##_start ,_##filename##__VA_ARGS__##_end }											\
//