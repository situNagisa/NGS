#pragma once

#include "../context.h"
#include "../algorithm.h"
#include "./vertex.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<vertex_buffer>... VertexBuffer>
struct layout : ::std::ranges::view_interface<layout<VertexBuffer...>>
{
	NGS_MPL_ENVIRON2(layout,::std::ranges::view_interface<layout<VertexBuffer...>>);
public:
	using context_type = contexts::vertex_array;
	using vertex_type = mpl::mstruct::storage<NGS_NS::layout::default_align, buffer_value_t<VertexBuffer>...>;
	using buffer_type = ::std::tuple< VertexBuffer...>;

	template<class... Ts>
	struct buffer_wrapper_type
	{
		NGS_MPL_ENVIRON_BEGIN(buffer_type);
	public:

		constexpr explicit(false) buffer_wrapper_type(auto&&... args) requires ::std::constructible_from<::std::tuple<Ts...>,decltype(args)...>
			: _data(NGS_PP_PERFECT_FORWARD(args)...)
		{}

		constexpr decltype(auto) operator=(const vertex_type& vertex) const
		{
			[&] <::std::size_t... Index>(::std::index_sequence<Index...>) {

				((this->template get<Index>() =  mpl::mstruct::storages::get<Index>(vertex)), ...);

			}(::std::make_index_sequence<sizeof...(VertexBuffer)>{});
		}

		template<::std::size_t Index> requires (Index < sizeof...(VertexBuffer))
		constexpr auto&& get() { return ::std::get<Index>(_data); }
		template<::std::size_t Index> requires (Index < sizeof...(VertexBuffer))
		constexpr auto&& get() const { return ::std::get<Index>(_data); }

		::std::tuple<Ts...> _data;
	};

	layout(bool normalized, auto&& buffer_tuple) requires ::std::constructible_from<buffer_type, decltype(buffer_tuple)>
		: _buffer(NGS_PP_PERFECT_FORWARD(buffer_tuple))
	{
		basic::bind(_context);
		::std::apply([&](auto&&... buffers)
			{
				algorithm::pipeline_layout<buffer_value_t<VertexBuffer>...>(_context, normalized, NGS_PP_PERFECT_FORWARD(buffers).get_context()...);
			}, _buffer);
	}
	template<class... Args>
		requires ((::std::constructible_from<VertexBuffer, Args&&...>) && ...)
	explicit(sizeof...(Args) == 0) layout(bool normalized, Args&&... args)
		: self_type(normalized, ::std::make_tuple(VertexBuffer{NGS_PP_PERFECT_FORWARD(args)...}...))
	{}

	constexpr auto size()const
	{
		if constexpr (!sizeof...(VertexBuffer))
		{
			return 0;
		}
		else
		{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
			if (!::std::is_constant_evaluated())
			{
				[this] <::std::size_t... Index>(::std::index_sequence<Index...>) {
					NGS_ASSERT(((::std::ranges::size(::std::get<0>(_buffer).data()) == ::std::ranges::size(::std::get<Index>(_buffer).data())) && ...));
				}(::std::make_index_sequence<sizeof...(VertexBuffer)>{});
			}
#endif
			return ::std::ranges::size(::std::get<0>(_buffer).data());
		}
	}

	template<class Buffer>
	static constexpr auto _access(Buffer buffer, ::std::ptrdiff_t index)
	{
		return[&]<::std::size_t... Index>(::std::index_sequence<Index...>) {
			return buffer_wrapper_type<
				decltype(::std::ranges::begin(::std::get<Index>(*buffer).data())[index])...
			>{
				(::std::ranges::begin(::std::get<Index>(*buffer).data())[index])...
			};
		}(::std::make_index_sequence<sizeof...(VertexBuffer)>{});
	}
	using difference_type = ::std::ptrdiff_t;
	using size_type = ::std::size_t;

	using iterator_type = nboost::stl_interfaces::iterators::range_index_random_access_iterator<buffer_type*, difference_type, _access<buffer_type*>>;
	using const_iterator_type = nboost::stl_interfaces::iterators::range_index_random_access_iterator<const buffer_type*, difference_type, _access<const buffer_type*>>;

	[[nodiscard]] constexpr auto begin() { return iterator_type{ &_buffer,0 }; }
	[[nodiscard]] constexpr auto end() { return iterator_type{ &_buffer,self_type::size() }; }
	[[nodiscard]] constexpr auto begin() const { return const_iterator_type{ &_buffer,0 }; }
	[[nodiscard]] constexpr auto end() const { return const_iterator_type{ &_buffer,self_type::size() }; }

	constexpr auto&& get_context() const { return _context; }
	void describe(enums::usage usage)
	{
		stl::tuples::for_each(_buffer, [usage](auto&& buffer)
			{
				basic::bind(NGS_PP_PERFECT_FORWARD(buffer).get_context());
				NGS_PP_PERFECT_FORWARD(buffer).describe(usage);
			});
	}

	void submit(auto&&... args)
		requires ::std::constructible_from<::std::ranges::subrange<::std::ranges::iterator_t<self_type>, ::std::ranges::sentinel_t<self_type>>, decltype(args)...>
	{
		auto subrange = ::std::ranges::subrange<::std::ranges::iterator_t<self_type>, ::std::ranges::sentinel_t<self_type>>{ NGS_PP_PERFECT_FORWARD(args)... };
		auto offset = ::std::ranges::distance(::std::ranges::begin(*this), ::std::ranges::begin(NGS_PP_PERFECT_FORWARD(subrange)));

		stl::tuples::for_each(_buffer, [&](auto&& buffer)
			{
				basic::bind(NGS_PP_PERFECT_FORWARD(buffer).get_context());
				NGS_PP_PERFECT_FORWARD(buffer).submit(offset, ::std::ranges::size(subrange));
			});
	}
	void submit(difference_type offset, size_type count)
	{
		self_type::submit(::std::ranges::begin(*this) + offset, ::std::ranges::begin(*this) + offset + count);
	}
	void submit() { self_type::submit(*this); }

	template<::std::size_t Index> requires (Index < sizeof...(VertexBuffer))
	auto&& get_buffer() { return ::std::get<Index>(_buffer); }
	template<::std::size_t Index> requires (Index < sizeof...(VertexBuffer))
	auto&& get_buffer() const { return ::std::get<Index>(_buffer); }

	void for_each_buffer(auto&& functor)
		requires ((::std::invocable<decltype(functor),VertexBuffer&>) && ...)
	{
		stl::tuples::for_each(_buffer, NGS_PP_PERFECT_FORWARD(functor));
	}
	//void for_each_buffer(auto&& functor) const
	//	requires ((::std::invocable<decltype(functor), const VertexBuffer&>) && ...)
	//{
	//	stl::tuples::for_each(_buffer, NGS_PP_PERFECT_FORWARD(functor));
	//}

	context_type _context;
	buffer_type _buffer;
};

NGS_LIB_MODULE_END