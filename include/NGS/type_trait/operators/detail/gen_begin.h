#include "../defined.h"

#undef _L
#undef _R

#define _GEN_OPERATOR_FORMAT(name,type,expression,...)				\
template<__VA_ARGS__>												\
struct name{														\
	using value_type = bool;										\
	constexpr static value_type value = requires{ expression; };	\
	using result_type = decltype([] {								\
		if constexpr (value) {										\
			return NGS_ declval<decltype(expression)>();			\
		}															\
		else {														\
			return NGS_ declval<na>();								\
		}															\
	}());															\
}																	\
//

#define _GEN_OPERATOR_UNARY(prefix,name,suffix,type,op)			\
_GEN_OPERATOR_FORMAT(											\
	prefix##name##suffix,										\
	type,														\
	op declval<_T>(),class _T);									\
template<class _T>												\
inline constexpr bool prefix##name##suffix##_v = prefix##name##suffix<_T>::value;\
template<class _T>												\
using type##_t = typename prefix##name##suffix<_T>::result_type	\
//

#define _GEN_OPERATOR_BINARY(prefix,name,suffix,type,op)			\
_GEN_OPERATOR_FORMAT(												\
	prefix##name##suffix,											\
	type,															\
	NGS_DECLVAL(_L) op NGS_DECLVAL(_R),class _L, class _R);			\
template<class _L, class _R = _L>									\
inline constexpr bool prefix##name##suffix##_v = prefix##name##suffix<_L,_R>::value;\
template<class _L, class _R = _L>									\
using type##_t = typename prefix##name##suffix<_L,_R>::result_type	\
//