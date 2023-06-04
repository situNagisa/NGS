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

#define _TYP            ::ngs::type::
#define NGS_TYPE        inline namespace type{
#define USE_NGS_TYPE    using namespace ::ngs::type;

#define _TYT                ::ngs::typetrait::
#define NGS_TYPE_TRAIT      namespace typetrait{
#define USE_NGS_TYTR        using namespace ::NGS::typetrait;

#define _CPT            ::ngs::cpt::
#define NGS_CONCEPT     inline namespace cpt{
#define USE_NGS_CONCEPT using namespace ::ngs::cpt;

#define NGS_INTERNAL        ngs_internal
#define NGS_INTERNAL_BEGIN  namespace ngs_internal{
#define NGS_USE_INTERNAL    using namespace ::ngs::ngs_internal;


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


//#define NGS_DEFAULT_TYPE				\
//NGS_TYPE_DEFINE(int,sign);              \
//NGS_TYPE_DEFINE(unsigned int,unsign)    \
//NGS_TYPE_DEFINE(size_t,size)			\
////

//#define NGS_GET(functionName,prop)\
//auto functionName(){return prop;}
//
//#define NGS_SET(functionName,prop,type)\
//void functionName(type v){prop = v;}
//
//#define NGS_GET_REF(functionName,prop)\
//auto& functionName(){return prop;}\
//auto& functionName()const {return prop;}
//
//#define NGS_FLAG_GET(functionName,flagName,bit)\
//bool functionName()const{return Bits(flagName,bit);}
//
//#define NGS_FLAG_SET(functionName,flagName,bit)\
//void functionName(_TYP BOOL v){Bits(flagName,bit,v);}
//
//#define NGS_FLAG(functionName,flagName,bit)\
//bool functionName()const{return Bits(flagName,bit);}   \
//void functionName(_TYP BOOL v){Bits(flagName,bit,v);}  

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
_NGS_TYPE_DEFINE(signed char, int8);
_NGS_TYPE_DEFINE(signed short, int16);
_NGS_TYPE_DEFINE(signed long, int32);
_NGS_TYPE_DEFINE(signed long long, int64);

_NGS_TYPE_DEFINE(unsigned char, uint8);
_NGS_TYPE_DEFINE(unsigned short, uint16);
_NGS_TYPE_DEFINE(unsigned long, uint32);
_NGS_TYPE_DEFINE(unsigned long long, uint64);

_NGS_TYPE_DEFINE(std::size_t, size_t);

//float
_NGS_TYPE_DEFINE(float, float32);
_NGS_TYPE_DEFINE(double, float64);

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


NGS_END

#endif // !__HEAD_NGS_NGS_Defined
