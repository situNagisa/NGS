#pragma once

#include "./defined.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template <class _Fn, class... _Types>
struct closure {
public:
	// We assume that _Fn is the type of a customization point object. That means
	// 1. The behavior of operator() is independent of cvref qualifiers, so we can use `invocable<_Fn, ` without
	//    loss of generality, and
	// 2. _Fn must be default-constructible and stateless, so we can create instances "on-the-fly" and avoid
	//    storing a copy.

	_STL_INTERNAL_STATIC_ASSERT((same_as<decay_t<_Types>, _Types> && ...));
	_STL_INTERNAL_STATIC_ASSERT(is_empty_v<_Fn>&& is_default_constructible_v<_Fn>);

	template <class... _UTypes>
		requires (same_as<decay_t<_UTypes>, _Types> && ...)
	constexpr explicit _Range_closure(_UTypes&&... _Args) noexcept(
		conjunction_v<is_nothrow_constructible<_Types, _UTypes>...>)
		: _Captures(_STD forward<_UTypes>(_Args)...) {}

	void operator()(auto&&) & = delete;
	void operator()(auto&&) const& = delete;
	void operator()(auto&&) && = delete;
	void operator()(auto&&) const&& = delete;

	using _Indices = index_sequence_for<_Types...>;

	template <class _Ty>
		requires invocable<_Fn, _Ty, _Types&...>
	constexpr decltype(auto) operator()(_Ty&& _Arg) & noexcept(
		noexcept(_Call(*this, _STD forward<_Ty>(_Arg), _Indices{}))) {
		return _Call(*this, _STD forward<_Ty>(_Arg), _Indices{});
	}

	template <class _Ty>
		requires invocable<_Fn, _Ty, const _Types&...>
	constexpr decltype(auto) operator()(_Ty&& _Arg) const& noexcept(
		noexcept(_Call(*this, _STD forward<_Ty>(_Arg), _Indices{}))) {
		return _Call(*this, _STD forward<_Ty>(_Arg), _Indices{});
	}

	template <class _Ty>
		requires invocable<_Fn, _Ty, _Types...>
	constexpr decltype(auto) operator()(_Ty&& _Arg) && noexcept(
		noexcept(_Call(_STD move(*this), _STD forward<_Ty>(_Arg), _Indices{}))) {
		return _Call(_STD move(*this), _STD forward<_Ty>(_Arg), _Indices{});
	}

	template <class _Ty>
		requires invocable<_Fn, _Ty, const _Types...>
	constexpr decltype(auto) operator()(_Ty&& _Arg) const&& noexcept(
		noexcept(_Call(_STD move(*this), _STD forward<_Ty>(_Arg), _Indices{}))) {
		return _Call(_STD move(*this), _STD forward<_Ty>(_Arg), _Indices{});
	}

private:
	template <class _SelfTy, class _Ty, size_t... _Idx>
	static constexpr decltype(auto) _Call(_SelfTy&& _Self, _Ty&& _Arg, index_sequence<_Idx...>) noexcept(
		noexcept(_Fn{}(_STD forward<_Ty>(_Arg), _STD get<_Idx>(_STD forward<_SelfTy>(_Self)._Captures)...))) {
		_STL_INTERNAL_STATIC_ASSERT(same_as<index_sequence<_Idx...>, _Indices>);
		return _Fn{}(_STD forward<_Ty>(_Arg), _STD get<_Idx>(_STD forward<_SelfTy>(_Self)._Captures)...);
	}

	tuple<_Types...> _Captures;
};

NGS_STATIC_FUNCTIONAL_END