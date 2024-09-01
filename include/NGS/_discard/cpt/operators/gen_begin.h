#include "../defined.h"

#define _GEN_OPERATOR_UNARY(name,depend)					\
template<class _Type>										\
concept name = type_traits::operators::depend##_v<_Type>	\
//

#define _GEN_OPERATOR_BINARY(name,depend)						\
template<class _Left, class _Right = _Left>						\
concept name = type_traits::operators::depend##_v<_Left,_Right>	\
//