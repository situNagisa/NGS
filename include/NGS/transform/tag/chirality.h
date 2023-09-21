#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN
namespace tag {
struct left_half {};
struct right_half {};
}
template<class _Tag>
concept CChirality = std::same_as<std::remove_cvref_t<_Tag>, tag::left_half> || std::same_as<std::remove_cvref_t<_Tag>, tag::right_half>;

NGS_CCPT_VERIFY(CChirality, tag::left_half);
NGS_CCPT_VERIFY(CChirality, tag::right_half);

NGS_TRANSFORM_END
