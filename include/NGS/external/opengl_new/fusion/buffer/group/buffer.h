#pragma once

#include "../../buffer.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<buffer>... Buffer>
struct buffer_group : ::std::ranges::view_interface<buffer_group<Buffer...>>
{
	NGS_MPL_ENVIRON2(buffer_group, ::std::ranges::view_interface<buffer_group<Buffer...>>);
public:
	using value_type = mpl::mstruct::storage<layout::default_align, buffer_value_t<Buffer>...>;
	using group_type = ::std::tuple<Buffer...>;

	explicit(false) buffer_group(auto&& buffer_group) requires ::std::constructible_from<group_type, decltype(buffer_group)>
		: _group(NGS_PP_PERFECT_FORWARD(buffer_group))
	{}
	template<class... Args>
		requires ((::std::constructible_from<Buffer, Args&&...>) && ...)
	explicit(sizeof...(Args) == 0) buffer_group(Args&&... args)
		: self_type(::std::make_tuple(Buffer{ NGS_PP_PERFECT_FORWARD(args)... }...))
	{}

	constexpr auto size()const
	{
		if constexpr (!sizeof...(Buffer))
		{
			return 0;
		}
		else
		{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
			if (!::std::is_constant_evaluated())
			{
				[this] <::std::size_t... Index>(::std::index_sequence<Index...>) {
					NGS_ASSERT(((::std::ranges::size(::std::get<0>(_group).data()) == ::std::ranges::size(::std::get<Index>(_group).data())) && ...));
				}(::std::make_index_sequence<sizeof...(Buffer)>{});
			}
#endif
			return ::std::ranges::size(::std::get<0>(_group).data());
		}
	}

	template<class... Ts>
	struct wrapper_type
	{
		constexpr explicit(false) wrapper_type(auto&&... args) requires ::std::constructible_from<::std::tuple<Ts...>, decltype(args)...>
			: _data(NGS_PP_PERFECT_FORWARD(args)...)
		{}

		constexpr wrapper_type& operator=(const value_type& vertex) const
		{
			[&] <::std::size_t... Index>(::std::index_sequence<Index...>) {

				((this->template get<Index>() = mpl::mstruct::storages::get<Index>(vertex)), ...);

			}(::std::make_index_sequence<sizeof...(Buffer)>{});
			return *this;
		}

		template<::std::size_t Index>
			requires (Index < sizeof...(Buffer))
		constexpr auto&& get() { return ::std::get<Index>(_data); }

		template<::std::size_t Index>
			requires (Index < sizeof...(Buffer))
		constexpr auto&& get() const { return ::std::get<Index>(_data); }

		::std::tuple<Ts...> _data;
	};

	static constexpr auto _access(auto buffer, ::std::ptrdiff_t index)
	{
		return[&]<::std::size_t... Index>(::std::index_sequence<Index...>) {
			return wrapper_type<decltype(::std::ranges::begin(::std::get<Index>(*buffer).data())[index])...>{
				(::std::ranges::begin(::std::get<Index>(*buffer).data())[index])...
			};
		}(::std::make_index_sequence<sizeof...(Buffer)>{});
	}
	using difference_type = ::std::ptrdiff_t;
	using size_type = ::std::size_t;

	using iterator_type = nboost::stl_interfaces::iterators::range_index_random_access_iterator<group_type*, difference_type, _access<group_type*>>;
	using const_iterator_type = nboost::stl_interfaces::iterators::range_index_random_access_iterator<const group_type*, difference_type, _access<const group_type*>>;

	[[nodiscard]] constexpr auto begin() { return iterator_type{ &_group,0 }; }
	[[nodiscard]] constexpr auto end() { return iterator_type{ &_group,self_type::size() }; }
	[[nodiscard]] constexpr auto begin() const { return const_iterator_type{ &_group,0 }; }
	[[nodiscard]] constexpr auto end() const { return const_iterator_type{ &_group,self_type::size() }; }

	void describe(enums::usage usage)
	{
		stl::tuples::for_each(_group, [usage](auto&& buffer)
			{
				contexts::bind(NGS_PP_PERFECT_FORWARD(buffer).get_context());
				NGS_PP_PERFECT_FORWARD(buffer).describe(usage);
			});
	}

	void submit(auto&&... args)
		requires ::std::constructible_from<::std::ranges::subrange<::std::ranges::iterator_t<self_type>, ::std::ranges::sentinel_t<self_type>>, decltype(args)...>
	{
		auto subrange = ::std::ranges::subrange<::std::ranges::iterator_t<self_type>, ::std::ranges::sentinel_t<self_type>>{ NGS_PP_PERFECT_FORWARD(args)... };
		auto offset = ::std::ranges::distance(::std::ranges::begin(*this), ::std::ranges::begin(NGS_PP_PERFECT_FORWARD(subrange)));

		stl::tuples::for_each(_group, [&](auto&& buffer)
			{
				contexts::bind(NGS_PP_PERFECT_FORWARD(buffer).get_context());
				NGS_PP_PERFECT_FORWARD(buffer).submit(offset, ::std::ranges::size(subrange));
			});
	}
	void submit(difference_type offset, size_type count)
	{
		self_type::submit(::std::ranges::begin(*this) + offset, ::std::ranges::begin(*this) + offset + count);
	}
	void submit() { self_type::submit(*this); }

	auto&& get_group() { return _group; }
	auto&& get_group() const { return _group; }

	template<::std::size_t Index>
		requires (Index < sizeof...(Buffer))
	auto&& get_buffer() { return ::std::get<Index>(_group); }
	template<::std::size_t Index>
		requires (Index < sizeof...(Buffer))
	auto&& get_buffer() const { return ::std::get<Index>(_group); }

	void for_each_buffer(auto&& functor)
		requires ((::std::invocable<decltype(functor), Buffer&>) && ...)
	{
		stl::tuples::for_each(_group, NGS_PP_PERFECT_FORWARD(functor));
	}

	group_type _group;
};

NGS_LIB_MODULE_END