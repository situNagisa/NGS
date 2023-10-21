#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

#define NGS_CPT_GEN_OPERATOR_UNARY(name,op)				\
template<class _Type>									\
concept can_##name = requires(_Type type) { op type; }	\
//

#define NGS_CPT_GEN_OPERATOR_BINARY(name,op)								\
template<class _Left, class _Right>											\
concept can_##name = requires(_Left left, _Right right) { left op right; };	\
//

#define NGS_CPT_GEN_OPERATOR_BINARY2(name,op)			\
NGS_CPT_GEN_OPERATOR_BINARY(name##_with,op);			\
template<class _Type>									\
concept can_##name = can_##name##_with<_Type, _Type>;	\
//

inline namespace operators {

//assign
//NGS_CPT_GEN_OPERATOR_BINARY2(assign, =);

//four operation
NGS_CPT_GEN_OPERATOR_UNARY(auto_increase, ++);
NGS_CPT_GEN_OPERATOR_UNARY(auto_decrease, --);
NGS_CPT_GEN_OPERATOR_BINARY2(plus, +);
NGS_CPT_GEN_OPERATOR_BINARY2(minus, -);
NGS_CPT_GEN_OPERATOR_BINARY2(muiltiply, *);
NGS_CPT_GEN_OPERATOR_BINARY2(divide, / );
NGS_CPT_GEN_OPERATOR_BINARY(plus_assign_from, +=);
NGS_CPT_GEN_OPERATOR_BINARY(minus_assign_from, -=);
NGS_CPT_GEN_OPERATOR_BINARY(muiltiply_assign_from, *=);
NGS_CPT_GEN_OPERATOR_BINARY(divide_assign_from, /=);

template<class _Left,class _Right>
concept can_four_operate_with =
	can_plus_with<_Left, _Right> ||
	can_minus_with<_Left, _Right> ||
	can_muiltiply_with<_Left, _Right> ||
	can_divide_with<_Left, _Right>;

template<class _Type>
concept can_four_operate = can_four_operate_with<_Type, _Type>;

//logic
NGS_CPT_GEN_OPERATOR_UNARY(not, !);
NGS_CPT_GEN_OPERATOR_BINARY2(and, &&);
NGS_CPT_GEN_OPERATOR_BINARY2(or, || );

template<class _Left, class _Right>
concept can_logic_operate_with =
	can_and_with<_Left, _Right> ||
	can_or_with<_Left, _Right>;

template<class _Type>
concept can_logic_operate = can_logic_operate_with<_Type, _Type> && can_not<_Type>;

//bit
NGS_CPT_GEN_OPERATOR_UNARY(not_bit, ~);
NGS_CPT_GEN_OPERATOR_BINARY2(and_bit, &);
NGS_CPT_GEN_OPERATOR_BINARY2(or_bit, | );
NGS_CPT_GEN_OPERATOR_BINARY(and_bit_assign_from, &=);
NGS_CPT_GEN_OPERATOR_BINARY(or_bit_assign_from, |=);
NGS_CPT_GEN_OPERATOR_BINARY(right_move_with, >> );
NGS_CPT_GEN_OPERATOR_BINARY(left_move_with, << );
NGS_CPT_GEN_OPERATOR_BINARY(right_move_assign_from, >>=);
NGS_CPT_GEN_OPERATOR_BINARY(left_move_assign_from, <<=);

template<class _Left, class _Right>
concept can_bit_operate_with =
	can_and_bit_with<_Left, _Right> ||
	can_or_bit_with<_Left, _Right> ||
	can_right_move_with<_Left, _Right> ||
	can_left_move_with<_Left, _Right>;

template<class _Type>
concept can_bit_operate = can_bit_operate_with<_Type, _Type>;

//sign
NGS_CPT_GEN_OPERATOR_UNARY(positive, +);
NGS_CPT_GEN_OPERATOR_UNARY(negative, -);

template<class _Type>
concept can_sign_operate = can_positive<_Type> && can_negative<_Type>;

//compare
NGS_CPT_GEN_OPERATOR_BINARY2(greater, > );
NGS_CPT_GEN_OPERATOR_BINARY2(less, < );
NGS_CPT_GEN_OPERATOR_BINARY2(equal, == );
NGS_CPT_GEN_OPERATOR_BINARY2(greater_equal, >= );
NGS_CPT_GEN_OPERATOR_BINARY2(less_equal, <= );
NGS_CPT_GEN_OPERATOR_BINARY2(three_way, <=> );

template<class _Left, class _Right>
concept can_compare_with =
	can_greater_with<_Left, _Right> ||
	can_less_with<_Left, _Right> ||
	can_equal_with<_Left, _Right> ||
	can_greater_equal_with<_Left, _Right> ||
	can_less_equal_with<_Left, _Right> ||
	can_three_way_with<_Left, _Right>;

template<class _Type>
concept can_compare = can_compare_with<_Type, _Type>;

//dereference
NGS_CPT_GEN_OPERATOR_UNARY(deref, *);

template<class _Type>
concept can_dereference = can_deref<_Type>;


}

#undef NGS_CPT_GEN_OPERATOR_UNARY
#undef NGS_CPT_GEN_OPERATOR_BINARY
#undef NGS_CPT_GEN_OPERATOR_BINARY2

NGS_CPT_END