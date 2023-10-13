//==========================================================================================================
// @file	:	NGS/NGS_Defined
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:10:17
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_NGS_Defined
#define __HEAD_NGS_NGS_Defined


#include "./STL.h"
#include "./precessor.h"

//============================
//命名空间
//============================
#define _NGS ::ngs::
#define NGS_BEGIN   namespace ngs{
#define NGS_END     };

#define NGS_TYPE_BEGIN  NGS_BEGIN inline namespace type{
#define NGS_TYPE_END	} NGS_END

#define NGS_CONCEPT     inline namespace cpt{

#define NGS_ARGS_PACKAGE(...) __VA_ARGS__

#ifdef NGS_CPP

#define NGS_C       extern "C"
#define NGS_C_BEGIN extern "C" {
#define NGS_C_END   };

#else

#define NGS_C       
#define NGS_C_BEGIN 
#define NGS_C_END   

#endif

NGS_TYPE_BEGIN

using void_t = void;
using void_ptr = void*;
using void_ptr_cst = const void*;

//char
_NGS_TYPE_DEFINE(char, nchar);

_NGS_TYPE_DEFINE(std::string, nstring);
_NGS_TYPE_DEFINE(std::string_view, nstring_view);

//int
_NGS_TYPE_DEFINE(std::int8_t, int8);
_NGS_TYPE_DEFINE(std::int16_t, int16);
_NGS_TYPE_DEFINE(std::int32_t, int32);
_NGS_TYPE_DEFINE(std::int64_t, int64);

_NGS_TYPE_DEFINE(std::uint8_t, uint8);
_NGS_TYPE_DEFINE(std::uint16_t, uint16);
_NGS_TYPE_DEFINE(std::uint32_t, uint32);
_NGS_TYPE_DEFINE(std::uint64_t, uint64);

_NGS_TYPE_DEFINE(std::size_t, size_t);

//float
_NGS_TYPE_DEFINE(std::float_t, float32);
_NGS_TYPE_DEFINE(std::double_t, float64);

//byte
//_NGS_TYPE_DEFINE(unsigned char, byte);

template<uint8 N>
struct NGS_API _byte_ { using type = uint8; };
template<>
struct NGS_API _byte_<0> { using type = uint8; };
template<>
struct NGS_API _byte_<1> { using type = uint8; };
template<>
struct NGS_API _byte_<2> { using type = uint16; };
template<>
struct NGS_API _byte_<3> { using type = uint32; };
template<>
struct NGS_API _byte_<4> { using type = uint32; };
template<>
struct NGS_API _byte_<5> { using type = uint64; };
template<>
struct NGS_API _byte_<6> { using type = uint64; };
template<>
struct NGS_API _byte_<7> { using type = uint64; };
template<>
struct NGS_API _byte_<8> { using type = uint64; };

template<uint8 N>
using byte_ = typename _byte_<N>::type;

_NGS_TYPE_DEFINE(byte_<0>, byte);

_NGS_TYPE_DEFINE(byte_<sizeof(void*)>, ptr_t);

NGS_TYPE_END

NGS_BEGIN

#if NGS_HAS_CPP_20
using source_location = std::source_location;
#else
using source_location = std::experimental::source_location;
#endif

NGS_END

#endif // !__HEAD_NGS_NGS_Defined
