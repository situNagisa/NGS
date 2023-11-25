#pragma once

#include "./defined.h"
#include "./concept.h"


#if defined(NGS_COMPILER_IS_MSVC)
#pragma warning(push)
#pragma warning(disable:4309)
#pragma warning(push)
#pragma warning(disable:4333)
#endif


NGS_COLOR_BEGIN

template<CChannel _A, CChannel _R, CChannel _G, CChannel _B>
struct NGS_DLL_API primary {
protected:
	using self_type = primary;
public:
	using alpha_type = _A;
	using red_type = _R;
	using green_type = _G;
	using blue_type = _B;

	constexpr static size_t bit_count = alpha_type::count + red_type::count + green_type::count + blue_type::count;
	constexpr static size_t byte_count = bits::as_byte(bit_count);

	using type = byte_<byte_count>;

	using std_type = byte_<bits::as_byte(standard_channel::count) * 4>;//4 is count of channel

	static constexpr size_t filter = alpha_type::filter_with_offset | red_type::filter_with_offset | green_type::filter_with_offset | blue_type::filter_with_offset;
	static constexpr color_format_d format{ .size = byte_count, };

public:

	constexpr primary() = default;
	explicit(false) constexpr primary(const type& value) : _value(value) {}
	constexpr primary(const self_type&) = default;
	constexpr self_type& operator=(const self_type&) = default;


	template<CPrimary _P>
	explicit(false) constexpr primary(_P&& color)
		: primary(
			(alpha_type	::template convert_from<typename _P::alpha_type>(color.alpha()) << alpha_type::offset) |
			(red_type	::template convert_from<typename _P::red_type>(color.red()) << red_type::offset) |
			(green_type	::template convert_from<typename _P::green_type>(color.green()) << green_type::offset) |
			(blue_type	::template convert_from<typename _P::blue_type>(color.blue()) << blue_type::offset)
		)
	{}
	self_type& operator=(CPrimary auto&& color) {
		_value = self_type(NGS_PP_PERFECT_FORWARD(color))._value;
		return *this;
	}

	constexpr decltype(auto) value()const { return _value; }

	constexpr decltype(auto) alpha()const { return ((_value >> alpha_type::offset) & alpha_type::filter); }
	constexpr decltype(auto) red()const { return ((_value >> red_type::offset) & red_type::filter); }
	constexpr decltype(auto) green()const { return ((_value >> green_type::offset) & green_type::filter); }
	constexpr decltype(auto) blue()const { return ((_value >> blue_type::offset) & blue_type::filter); }

	constexpr decltype(auto) alpha_percent()const { return alpha_type::percent(alpha()); }
	constexpr decltype(auto) red_percent()const { return red_type::percent(red()); }
	constexpr decltype(auto) green_percent()const { return green_type::percent(green()); }
	constexpr decltype(auto) blue_percent()const { return blue_type::percent(blue()); }

	constexpr void set_alpha(const typename alpha_type::type& a)const
	{
		_value = ((a << alpha_type::offset) & alpha_type::filter_with_offset) | (_value & ~alpha_type::filter_with_offset);
	}
	constexpr void set_red(const typename red_type::type& r)const
	{
		_value = ((r << red_type::offset) & red_type::filter_with_offset) | (_value & ~red_type::filter_with_offset);
	}
	constexpr void set_green(const typename green_type::type& g)const
	{
		_value = ((g << green_type::offset) & green_type::filter_with_offset) | (_value & ~green_type::filter_with_offset);
	}
	constexpr void set_blue(const typename blue_type::type& b)const
	{
		_value = ((b << blue_type::offset) & blue_type::filter_with_offset) | (_value & ~blue_type::filter_with_offset);
	}

public:
	//this public member variable is for non-type template parameter
	type _value{};
};

#define NGS_DEFINE_PRIMARY(c1,c2,c3,c4)		\
template<size_t _##c1, size_t _##c2, size_t _##c3, size_t _##c4> \
struct NGS_DLL_API c1##c2##c3##c4 : public primary<channel<_##c1, _##c2 + _##c3 + _##c4>, channel<_##c2, _##c3 + _##c4>, channel<_##c3, _##c4>, channel<_##c4, 0>> { \
	NGS_MPL_ENVIRON(c1##c2##c3##c4);			\
public:											\
	NGS_MPL_INHERIT_TYPE(alpha_type,base_type);	\
	NGS_MPL_INHERIT_TYPE(red_type,base_type);	\
	NGS_MPL_INHERIT_TYPE(green_type,base_type);	\
	NGS_MPL_INHERIT_TYPE(blue_type,base_type);	\
	using base_type::base_type;					\
	constexpr c1##c2##c3##c4(					\
		standard_channel::type c1##_,			\
		standard_channel::type c2##_,			\
		standard_channel::type c3##_,			\
		standard_channel::type c4##_			\
	)											\
	: base_type(								\
		(alpha_type	::template convert_from<standard_channel>(A_) << alpha_type::offset)|	\
		(red_type	::template convert_from<standard_channel>(R_) << red_type::offset)	|	\
		(green_type	::template convert_from<standard_channel>(G_) << green_type::offset)|	\
		(blue_type	::template convert_from<standard_channel>(B_) << blue_type::offset)		\
		)									\
	{}										\
};											\
using c1##c2##c3##c4##32 = c1##c2##c3##c4<8, 8, 8, 8>;	\
using c1##c2##c3##c4##24 = c1##c2##c3##c4<0, 8, 8, 8>;	\
using c1##c2##c3##c4##16 = c1##c2##c3##c4<0, 5, 6, 5>;	\
using c1##c2##c3##c4##15 = c1##c2##c3##c4<1, 5, 5, 5>;	\
using c1##c2##c3##c4##8 = c1##c2##c3##c4<0, 3, 3, 2>;	\
using standard_##c1##c2##c3##c4 = c1##c2##c3##c4##32;	\
static_assert(CPrimary<standard_##c1##c2##c3##c4>)		\
//

NGS_DEFINE_PRIMARY(A, R, G, B);
NGS_DEFINE_PRIMARY(A, R, B, G);
NGS_DEFINE_PRIMARY(A, G, R, B);
NGS_DEFINE_PRIMARY(A, G, B, R);
NGS_DEFINE_PRIMARY(A, B, R, G);
NGS_DEFINE_PRIMARY(A, B, G, R);

NGS_DEFINE_PRIMARY(R, A, G, B);
NGS_DEFINE_PRIMARY(R, A, B, G);
NGS_DEFINE_PRIMARY(R, G, A, B);
NGS_DEFINE_PRIMARY(R, G, B, A);
NGS_DEFINE_PRIMARY(R, B, A, G);
NGS_DEFINE_PRIMARY(R, B, G, A);

NGS_DEFINE_PRIMARY(G, A, R, B);
NGS_DEFINE_PRIMARY(G, A, B, R);
NGS_DEFINE_PRIMARY(G, R, A, B);
NGS_DEFINE_PRIMARY(G, R, B, A);
NGS_DEFINE_PRIMARY(G, B, A, R);
NGS_DEFINE_PRIMARY(G, B, R, A);

NGS_DEFINE_PRIMARY(B, A, R, G);
NGS_DEFINE_PRIMARY(B, A, G, R);
NGS_DEFINE_PRIMARY(B, R, A, G);
NGS_DEFINE_PRIMARY(B, R, G, A);
NGS_DEFINE_PRIMARY(B, G, A, R);
NGS_DEFINE_PRIMARY(B, G, R, A);

#undef NGS_DEFINE_PRIMARY

NGS_COLOR_END

#if defined(NGS_COMPILER_IS_MSVC)
#pragma warning(pop)
#pragma warning(pop)
#endif
