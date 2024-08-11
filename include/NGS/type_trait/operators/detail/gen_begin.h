#include "../defined.h"

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
	op declval<T>(),class T);									\
template<class T>												\
inline constexpr bool prefix##name##suffix##_v = prefix##name##suffix<T>::value;\
template<class T>												\
using type##_t = typename prefix##name##suffix<T>::result_type	\
//

#define _GEN_OPERATOR_BINARY(prefix,name,suffix,type,op)			\
_GEN_OPERATOR_FORMAT(												\
	prefix##name##suffix,											\
	type,															\
	NGS_DECLVAL(L) op NGS_DECLVAL(R),class L, class R);			\
template<class L, class R = L>									\
inline constexpr bool prefix##name##suffix##_v = prefix##name##suffix<L,R>::value;\
template<class L, class R = L>									\
using type##_t = typename prefix##name##suffix<L,R>::result_type	\
//