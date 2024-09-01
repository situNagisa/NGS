#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_DEFAULT(attachment_target, constexpr static auto value = 0ull; );
NGS_TCEA_TRAIT_ALIAS_V(attachment_target);
NGS_TCEA_TRAIT_HAS_VALUE(attachment_target, target);
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(value);
NGS_TCEA_TRAIT_DEFAULT(attachment_value);
NGS_TCEA_TRAIT_ALIAS_T(attachment_value);
template<class T>
	requires requires(T t) { { value(t) }; }
struct attachment_value<T>
{
	using type = ::std::remove_cvref_t<decltype(value(::std::declval<T>()))>;
};


template<enums::framebuffer_attachment Attachment, class T>
struct basic_attachment
{
	constexpr static auto target = Attachment;
	using value_type = T;

	auto&& value(this auto&& self) { return self._value; }

	value_type _value;
};

template<class T>
concept attachable = ::std::convertible_to<decltype(attachment_target_v<::std::remove_cv_t<T>>), enums::framebuffer_attachment>
	&& (textures::texture<attachment_value_t<::std::remove_cv_t<T>>> 
		|| renderbuffers::renderable<attachment_value_t<::std::remove_cv_t<T>>>
		);

template<enums::framebuffer_attachment Attachment>
constexpr decltype(auto) make_attachment(auto&& value)
{
	using type = ::std::remove_cvref_t<decltype(value)>;
	if constexpr(::std::semiregular<type>)
	{
		return basic_attachment<Attachment, type>(NGS_PP_PERFECT_FORWARD(value));
	}
	else
	{
		return basic_attachment<Attachment, decltype(value)>(NGS_PP_PERFECT_FORWARD(value));
	}
}

NGS_LIB_MODULE_END