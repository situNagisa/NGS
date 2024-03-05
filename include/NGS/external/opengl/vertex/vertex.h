#pragma once

#include "./array.h"
#include "./buffer.h"
#include "./buffer_array.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vertex_info
{
	enums::usage usage;
	bool normalized = false;
};

template<vertex_buffer_descriptor... Buffers>
struct vertex : ::std::ranges::view_interface<vertex<Buffers...>>
{
	NGS_MPL_ENVIRON_BEGIN(vertex);
public:
	using value_type = ::std::tuple<Buffers&...>;
	using const_value_type = ::std::tuple<const Buffers&...>;
	using vertex_struct_type = mpl::mstruct::storage<layout::default_align, Buffers...>;

	vertex(self_type&&) = default;
	constexpr self_type& operator=(self_type&&) = default;

	vertex(const vertex_info& info)
		: _buffers(buffer<Buffers>(info.usage)...)
		, _size()
	{
		NGS_LIB_MODULE_NAME::commit_layout(_array, info.normalized, _buffers.data());
	}

	constexpr auto vertex_size()const { return _size; }
	constexpr auto size() const
	{
		if constexpr(!sizeof...(Buffers))
		{
			return 0;
		}
		else
		{
			return ::std::get<0>(_buffers.data()).data().size();
		}
	}

	void push_back(const vertex_struct_type& vertex_struct)
	{
		[&] <::std::size_t... Index>(::std::index_sequence<Index...>) {

			((::std::get<Index>(_buffers.data()).data().push_back(mpl::mstruct::storages::get<Index>(vertex_struct))),...);

		}(::std::make_index_sequence<sizeof...(Buffers)>{});
	}

	void emplace_back(const Buffers&... buffers)
	{
		self_type::push_back(vertex_struct_type{ buffers... });
	}

	void update(enums::usage usage)
	{
		_size = size();
		stl::tuples::for_each(_buffers.data(), [usage](auto&& buffer)
			{
				basic::bind(NGS_PP_PERFECT_FORWARD(buffer));
				NGS_PP_PERFECT_FORWARD(buffer).update(usage);
			});
	}
	void submit(::std::size_t begin, ::std::size_t count)const
	{
		NGS_ASSERT(begin + count <= _size);
		stl::tuples::for_each(_buffers.data(), [begin,count](auto&& buffer)
			{
				basic::bind(NGS_PP_PERFECT_FORWARD(buffer));
				NGS_PP_PERFECT_FORWARD(buffer).submit(begin,count);
			});
	}

	auto&& get_vertex_array() { return _array; }
	auto&& get_vertex_array() const { return _array; }

	vertex_array _array{};
	buffer_array<buffer<Buffers>...> _buffers;
	::std::size_t _size = 0;
};

namespace _detail
{
	template<class T,class = ::std::make_index_sequence<mpl::mstruct::field_count_v<typename T::vertex_struct_type>>>
	struct at_t;

	template<class Vertex,::std::size_t... Index>
	struct at_t<Vertex,::std::index_sequence<Index...>>
	{

		decltype(auto) operator()(Vertex* v, ::std::ptrdiff_t index)const
		{
			return typename Vertex::value_type{::std::get<Index>(v->_buffers.data()).data()[index]...};
		}
		decltype(auto) operator()(const Vertex* v, ::std::ptrdiff_t index)const
		{
			return typename Vertex::const_value_type{::std::get<Index>(v->_buffers.data()).data()[index]...};
		}
	};

	template<class T>
	inline constexpr at_t<type_traits::naked_t<T>> at{};
	
	template<class T>
	struct iterator
	{
		using object_type = type_traits::object_t<T>;
		using value_type = ::std::conditional_t<::std::is_const_v<object_type>,typename object_type::const_value_type,typename object_type::value_type>;
		using type = nboost::stl_interfaces::iterators::range_index_random_access_iterator<object_type*, ::std::ptrdiff_t, at<T>>;
	};

	template<class T>
	using iterator_t = typename iterator<T>::type;
}

constexpr auto begin(cpt::derived_from_specialization<vertex> auto&& vertex)
{
	using iterator_type = _detail::iterator_t<decltype(vertex)>;
	return iterator_type{ &vertex, 0 };
}
constexpr auto end(cpt::derived_from_specialization<vertex> auto&& vertex)
{
	using iterator_type = _detail::iterator_t<decltype(vertex)>;
	return iterator_type{ &vertex, static_cast<typename iterator_type::difference_type>(vertex.size()) };
}

NGS_LIB_MODULE_END