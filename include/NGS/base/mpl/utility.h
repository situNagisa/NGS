#pragma once
#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(size_of_sequence, class _Element, class... _Sequence) {
private:
	template<class _ElementType, class... _ElementTypes>
	constexpr static size_t _SizeOf() {
		size_t size = sizeof(_ElementType);
		if constexpr (sizeof...(_ElementTypes)) size += _SizeOf<_ElementTypes...>();
		return size;
	}
public:
	NGS_mreturn _SizeOf<_Element, _Sequence...>();
};

NGS_END
NGS_END
