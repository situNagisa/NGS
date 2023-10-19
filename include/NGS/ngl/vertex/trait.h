#pragma once

#include "NGS/ngl/defined.h"


NGL_BEGIN
namespace tag {
/**
 * 									buffer_type							  buffer_type				buffer_type   buf3	...
 * 									⬇									  ⬇							⬇		 ⬇		...
 * 					|				-----------------------------------------------------------------------
 * 					|	vertex0 ->	| attrib_type,attrib_type,attrib_type | attrib_type,attrib_type | ... | ... |	...
 * 					|				----------------------------------------------------------------------
 * 					|				-----------------------------------------------------------------------
 * vertex array  ⬅	|	vertex1 ->	| attrib_type,attrib_type,attrib_type | attrib_type,attrib_type | ... | ... |	...
 * 					|				----------------------------------------------------------------------
 * 					|		.
 * 					|		.
 * 					|		.
 *
*/


template<class  _ElementType>
struct NGS_API Attrib {
	using element_type = _ElementType;
	using iterator_type = const element_type*;
	using type = iterator_type;
};
template<class  _ElementType>
struct NGS_API Buffer {
	using element_type = _ElementType;
	using iterator_type = const element_type*;
	using type = iterator_type;
};
template<class  _ElementType>
struct NGS_API Vertex {
	using element_type = Buffer<_ElementType>::type;
	using iterator_type = const element_type*;
	using type = iterator_type;
};
template<class  _ElementType>
struct NGS_API Array {
	using element_type = Vertex<_ElementType>::type;
	using iterator_type = const element_type*;
	using type = iterator_type;
};
};
namespace trait {
NGS_MPL_FUNCTION(range, class  _Tag) { using type = typename _Tag::iterator_type*; };
template<class  _Tag>
using range_t = typename range<_Tag>::type;
};
NGL_END
