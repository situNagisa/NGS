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


#include "NGS/base/STL.h"

//============================
//命名空间
//============================
#define _NGS        ::ngs::
#define NGS_BEGIN   namespace ngs{
#define NGS_END     };
#define USE_NGS     using namespace ::ngs;

#define _NGS_TYP            ::ngs::type::
#define NGS_TYPE        inline namespace type{
#define USE_NGS_TYPE    using namespace ::ngs::type;

#define _NGS_TYT                ::ngs::type_trait::
#define NGS_TYPE_TRAIT		namespace type_trait{
#define USE_NGS_TYTR        using namespace ::NGS::type_trait;

#define _NGS_CPT            ::ngs::cpt::
#define NGS_CONCEPT     inline namespace cpt{
#define USE_NGS_CONCEPT using namespace ::ngs::cpt;

#define _NGS_MPL 		  ::ngs::mpl::
#define NGS_MPL_BEGIN	namespace mpl{


#define NGS_TYPE_DEFINE(type,id)        \
using __##id    = type;                 \
using __##id##_cst = const type;        \
using __##id##_ref = type&;             \
using __##id##_ref_cst = const type&;   \
using __##id##_right = type&&;			\
using __##id##_right_cst = const type&&;\
using __##id##_ptr = type*;             \
using __##id##_ptr_cst = const type*;	\
//


#define _NGS_TYPE_DEFINE(type,id)   	\
using id    = type;                 	\
using id##_cst = const type;        	\
using id##_ref = type&;             	\
using id##_ref_cst = const type&;   	\
using id##_right = type&&;				\
using id##_right_cst = const type&&;	\
using id##_ptr = type*;             	\
using id##_ptr_cst = const type*;		\
//

#define NGS_DEFINE_TYPE(id,...)			\
using id##_t = ##__VA_ARGS__;			\
using id##_cst = const id##_t;			\
using id##_ref = id##_t&;				\
using id##_ref_cst = const id##_t&;		\
using id##_rref = id##_t&&;				\
using id##_rref_cst = const id##_t&&;	\
using id##_ptr = id##_t*;				\
using id##_ptr_cst = const id##_t*		\
//



#if NGS_BUILD_TYPE == NGS_DEBUG
#define NGS_DEBUG_EXPR(expr) expr
#else
#define NGS_DEBUG_EXPR(expr)
#endif

//============================
//设置
//============================
#ifdef __cplusplus

#define NGS_C       extern "C"
#define NGS_C_BEGIN extern "C" {
#define NGS_C_END   };

#else

#define NGS_C       
#define NGS_C_BEGIN 
#define NGS_C_END   

#endif
//============================
//补充
//============================

NGS_BEGIN

NGS_TYPE

using void_t = void;
using void_ptr = void*;
using void_ptr_cst = const void*;

//char
_NGS_TYPE_DEFINE(char, nchar);

_NGS_TYPE_DEFINE(std::string, nstring);
_NGS_TYPE_DEFINE(std::string_view, nstring_view);

using ostream = std::basic_ostream<nchar, std::char_traits<nchar> >;

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
struct _byte_ { using type = uint8; };
template<>
struct _byte_<0> { using type = uint8; };
template<>
struct _byte_<1> { using type = uint8; };
template<>
struct _byte_<2> { using type = uint16; };
template<>
struct _byte_<3> { using type = uint32; };
template<>
struct _byte_<4> { using type = uint32; };
template<>
struct _byte_<5> { using type = uint64; };
template<>
struct _byte_<6> { using type = uint64; };
template<>
struct _byte_<7> { using type = uint64; };
template<>
struct _byte_<8> { using type = uint64; };

template<uint8 N>
using byte_ = typename _byte_<N>::type;

_NGS_TYPE_DEFINE(byte_<0>, byte);

_NGS_TYPE_DEFINE(byte_<sizeof(void*)>, ptr_t);

NGS_END

#if NGS_HAS_CPP_20
using source_location = std::source_location;
#else
using source_location = std::experimental::source_location;
#endif

#define NGS_DECLARE_TV(id,value_t)		\
template<class>							\
constexpr value_t id##_convert = {};	\
template<value_t>						\
struct _##id##Convert;					\
template<value_t _Value>				\
using id##_convert_t = typename _##id##Convert<_Value>::type;\
//

#define NGS_DEFINE_TV(id,value_t,type,value)	\
template<>										\
constexpr value_t id##_convert<type> = value;	\
template<>										\
struct _##id##Convert<value> { using type = type; }; \
//





NGS_END

#endif // !__HEAD_NGS_NGS_Defined
