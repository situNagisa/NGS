#pragma once

#include "NGS/ngl/vertex/array/base.h"
#include "NGS/ngl/vertex/concepts.h"
#include "../fusion.h"

NGL_BEGIN
NGL_OBJ_BEGIN

template<class, class, fusion::CBuffer...>
class NGS_API  _VertexArray;

template<fusion::CBuffer... _Buffers, size_t... _BufferIndex, size_t... _AttribIndex>
class NGS_API  _VertexArray<std::index_sequence<_BufferIndex...>, std::index_sequence<_AttribIndex...>, _Buffers...> : public VertexArrayBase {
	NGS_MPL_ENVIRON(_VertexArray);
private:
	using _sequence = mpl::vector<_Buffers...>;
public:
	using base = VertexArrayBase;
	using this_t = _VertexArray;
	constexpr static size_t element_count = (_Buffers::element_count + ...);
	constexpr static size_t buffer_count = sizeof...(_BufferIndex);
	constexpr static size_t attrib_count = sizeof...(_AttribIndex);

	template<size_t _Index> using buffer_at_t = typename _sequence::template at_c<_Index>;
	template<size_t _Index> using buffer_element_type = typename buffer_at_t<_Index>::element_type;

	_VertexArray(size_t count, Usage usage)
		: base(factories::make_vertex<_Buffers...>(count, usage))
		, _max_count(count)
	{}
	_VertexArray(_VertexArray&& other)
		: base(std::move(other))
		, _max_count(other._max_count)
	{}

protected:
	template<size_t _Index> using _add_vertex_param_buffer_t = base::tag_buffer::type;
	template<size_t _Index> using _add_vertex_param_buffers_t = const buffer_element_type<_Index>*;

	template<size_t _Index, class  T> using _add_vertex_param_transform_t = T&&;

	template<size_t _Index, template<class, size_t>class  _C>
	using _add_vertex_param_container_t = _C<buffer_element_type<_Index>, buffer_at_t<_Index>::element_count>;

#define _NGL_VAO_BUF_T(id,meta_depend) typename meta_depend::template _add_vertex_param_##id##_t<_BufferIndex>...
#define _NGL_VAO_BUF_TRA_T(transform_type,meta_depend) typename meta_depend::template _add_vertex_param_transform_t<_BufferIndex,transform_type>...

#define _NGL_VAO_BUF_VIEW(meta_depend) meta_depend::template _add_vertex_param_container_t<_BufferIndex,std::span>...
#define _NGL_VAO_BUF_CONTAINER(meta_depend) meta_depend::template _add_vertex_param_container_t<_BufferIndex,std::array> const&...

	//#define _NGL_VAO_ATT_T(id,meta_depend) typename meta_depend::template _add_vertex_param_##id##_t<_AttribIndex>...
	//#define _NGL_VAO_ATT_TRA_T(transform_type,meta_depend) typename meta_depend::template _add_vertex_param_transform_t<_AttribIndex,transform_type>...
public:
	template<size_t _I>
	struct _Param {
		using _element_type = buffer_element_type<_I>;
		constexpr static size_t _element_count = buffer_at_t<_I>::element_count;

		template<class _Rng>
			requires std::ranges::random_access_range<_Rng>&&
			//requires(std::ranges::range_value_t<_Rng> value) { { static_cast<_element_type>(value) } -> std::same_as<_element_type>; }
			std::convertible_to<const std::ranges::range_value_t<_Rng>*, const _element_type*>
		explicit(false) _Param(const _Rng& range)
			: ptr(static_cast<const _element_type*>(std::ranges::cdata(range)))
		{}
		explicit(false) _Param(std::initializer_list<_element_type> list)
			: ptr(std::ranges::cdata(list))
		{}
		//explicit(false) _Param(const _element_type* ptr)
		//	: ptr(ptr)
		//{}

		const _element_type* ptr;
	};
public:
	using base::AddVertexes;

	void AddVertexes(size_t count, _NGL_VAO_BUF_T(buffers, this_t) buffers) { base::AddVertexes(count, std::array<typename base::tag_buffer::type, buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	//void AddVertexes(size_t count, _NGL_VAO_BUF_VIEW(this_t) buffers) { base::AddVertexes(count, std::array<typename base::tag_buffer::type, buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	//void AddVertexes(size_t count, _NGL_VAO_BUF_CONTAINER(this_t) buffers) { base::AddVertexes(count, std::array<typename base::tag_buffer::type, buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	
	void AddVertexes(size_t count, _Param<_BufferIndex>... params){
		base::AddVertexes(count, std::array<typename base::tag_buffer::type, buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(params.ptr))...});
	}
	bool IsFull()const { return _count == _max_count; }
private:
	size_t _max_count;
};
																																								
#define _NGL_VAO_DERIVED_FROM(base_class,derived_class)																											\
template<class , class , fusion::CBuffer...>																													\
class NGS_API  _##derived_class;																																\
template<fusion::CBuffer... _Buffers>																															\
using derived_class = _##derived_class<std::index_sequence_for<_Buffers...>, std::make_index_sequence<(_Buffers::variable_count + ...)>, _Buffers...>;			\
template<fusion::CBuffer... _Buffers, size_t... _BufferIndex, size_t... _AttribIndex>																			\
class NGS_API  _##derived_class<std::index_sequence<_BufferIndex...>, std::index_sequence<_AttribIndex...>, _Buffers...> : public base_class<_Buffers...>		\
//

template<fusion::CBuffer... _Buffers>
using VertexArray = _VertexArray<std::index_sequence_for<_Buffers...>, std::make_index_sequence<(_Buffers::variable_count + ...)>, _Buffers...>;

NGS_END
NGL_END
