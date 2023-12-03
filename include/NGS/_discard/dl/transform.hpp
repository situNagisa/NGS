#pragma once

#include "NGS/dl/transform.h"

NGS_DL_BEGIN

NGS_HPP_INLINE matrix_type Transform::GetMatrix() const
{
	matrix_type matrix = identity_matrix;
	return mla::translate(position + offset) * mla::rotate(rotation) * mla::scale(scale);
}

NGS_DL_END
