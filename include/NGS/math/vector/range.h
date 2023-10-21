#pragma once

#include "./expression.h"
#include "./container.h"

NGS_MATH_VECTOR_BEGIN

namespace detail
{

template<functor::accessible _Type>
struct vector_expression_iterator :
	nboost::stl_interfaces::base_random_access_iterator<
	vector_expression_iterator<_Type>,
	functor::vector_value_t<_Type>
	>
{
	NGS_MPL_ENVIRON2(vector_expression_iterator,
		nboost::stl_interfaces::base_random_access_iterator<
		vector_expression_iterator<_Type>,
		functor::vector_value_t<_Type>
		>);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	NGS_MPL_INHERIT_TYPE(reference, base_type);
	NGS_MPL_INHERIT_TYPE(pointer, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);

	using range_type = _Type;
public:
	using base_type::base_type;
	constexpr vector_expression_iterator(range_type* range, size_t index)
		: _range(range)
		, _index(index)
	{}
	constexpr vector_expression_iterator() = default;

	constexpr iterator_type& operator+=(difference_type n) {
		_index += n;
		return base_type::_derived();
	}
	constexpr difference_type operator-(self_type other)const { return other._index - _index; }

	constexpr decltype(auto) operator*()const {
		return functor::access(*_range, _index);
	}
private:
	range_type* _range = nullptr;
	size_t _index = 0;
};
}

template<functor::accessible _Type>
struct iterator
{
	using input = detail::vector_expression_iterator<const _Type>;
	using reverse_input = detail::vector_expression_iterator<const _Type>;
};
template<functor::accessible _Type>
	requires functor::assignable<functor::vector_value_t<_Type>,_Type>
struct iterator<_Type>
{
	using input = detail::vector_expression_iterator<const _Type>;
	using reverse_input = detail::vector_expression_iterator<const _Type>;

	using input_or_output = detail::vector_expression_iterator<_Type>;
	using reverse_input_or_output = detail::vector_expression_iterator<_Type>;
};

template<functor::accessible _Type>
using in_iterator_t = typename iterator<_Type>::input;
template<functor::accessible _Type>
using reverse_in_iterator_t = typename iterator<_Type>::reverse_input;
template<functor::accessible _Type>
	requires functor::assignable<functor::vector_value_t<_Type>,_Type>
using io_iterator_t = typename iterator<_Type>::input_or_output;
template<functor::accessible _Type>
	requires functor::assignable<functor::vector_value_t<_Type>,_Type>
using reverse_io_iterator_t = typename iterator<_Type>::reverse_input_or_output;

template<functor::container _Vector>
constexpr decltype(auto) begin(_Vector& vector){return io_iterator_t<_Vector>(&vector, 0);}
template<functor::container _Vector>
constexpr decltype(auto) end(_Vector& vector){return io_iterator_t<_Vector>(&vector, functor::dimension<_Vector>);}
template<functor::expression _Vector>
constexpr decltype(auto) begin(const _Vector& vector){return in_iterator_t<_Vector>(&vector, 0);}
template<functor::expression _Vector>
constexpr decltype(auto) end(const _Vector& vector){return in_iterator_t<_Vector>(&vector, functor::dimension<_Vector>);}

template<functor::container _Vector>
constexpr decltype(auto) rbegin(_Vector& vector){return reverse_io_iterator_t<_Vector>(&vector, vector.size() - 1);}
template<functor::container _Vector>
constexpr decltype(auto) rend(_Vector& vector){return reverse_io_iterator_t<_Vector>(&vector, -1);}
template<functor::expression _Vector>
constexpr decltype(auto) rbegin(const _Vector& vector){return reverse_in_iterator_t<_Vector>(&vector, vector.size() - 1);}
template<functor::expression _Vector>
constexpr decltype(auto) rend(const _Vector& vector){return reverse_in_iterator_t<_Vector>(&vector, -1);}

template<functor::expression _Vector>
constexpr decltype(auto) cbegin(const _Vector& vector){return begin(vector);}
template<functor::expression _Vector>
constexpr decltype(auto) cend(const _Vector& vector){return end(vector);}
template<functor::expression _Vector>
constexpr decltype(auto) crbegin(const _Vector& vector){return rbegin(vector);}
template<functor::expression _Vector>
constexpr decltype(auto) crend(const _Vector& vector){return rend(vector);}

NGS_MATH_VECTOR_END