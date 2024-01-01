#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class...>
struct packer
{
protected:
	using self_type = packer;
public:
	using master_pack_type = self_type;
	constexpr static size_t count = 0;

	constexpr packer() = default;

	template<size_t>
	constexpr void get()const {}
};

template<class _First, class... _Rest>
struct packer<_First, _Rest...> : packer<_Rest...>
{
	NGS_MPL_ENVIRON(packer);
public:
	using sequence_type = self_type;
	constexpr static size_t count = sizeof...(_Rest) + 1;

	constexpr packer() = default;
	constexpr packer(auto&& first, auto&&... rest)
		: base_type(NGS_PP_PERFECT_FORWARD(rest)...)
		, _param(NGS_PP_PERFECT_FORWARD(first))
	{}

protected:

	template<size_t _Index>
	constexpr static auto&& _get_impl(auto&& self) //c++ 20 is not support display this
	{
		constexpr auto index = _Index;

		NGS_ASSERT_IF_CONSTEXPR(index < count, "index out of range")
		{
			if constexpr (index == count - 1)
			{
				return self._param;
			}
			else
			{
				using forward_base_type = type_traits::add_cvref_like_t<decltype(self), base_type>;
				return base_type::template _get_impl<index>(static_cast<forward_base_type>(self));
			}
		}
	}
public:

	template<size_t _Index>
	constexpr decltype(auto) get()
	{
		return self_type::template _get_impl<count - _Index - 1>(*this);
	}
	template<size_t _Index>
	constexpr decltype(auto) get() const
	{
		return self_type::template _get_impl<count - _Index - 1>(*this);
	}

	//this `public` is for `structured type`
public:
	_First _param;
};

#if defined(__cpp_deduction_guides)
template<class... _Args>
packer(_Args&&...) -> packer<_Args...>;
#endif


NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(packer);