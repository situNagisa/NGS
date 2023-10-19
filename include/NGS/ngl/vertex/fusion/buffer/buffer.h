#pragma once

#include "./concept.h"
#include "../attrib/make.h"

NGS_NGL_FUSION_BEGIN

template<CFundamental _Type, size_t... _Counts>
struct buffer : mpl::mstruct::structure<layout::no_align_t, _Type[_Counts]...> {
	NGS_MPL_ENVIRON(buffer);
public:
	using element_type = _Type;
	constexpr static size_t element_count = (_Counts + ...);
	constexpr static size_t attrib_count = sizeof...(_Counts);

	constexpr static auto GET_ATTRIBS() {
		std::array<attrib_dynamic_data, attrib_count> attribs{
			make_attrib<element_type,_Counts>()...
		};
		constexpr auto variables = base_type::GET_VARIABLES();
		for (size_t i = 0; i < attrib_count; i++)
		{
			attribs[i].offset = variables[i].offset;
		}
		return attribs;
	}
};


NGS_NGL_FUSION_END
