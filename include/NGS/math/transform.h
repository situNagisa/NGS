#pragma once

#include "NGS/base/base.h"
#include "NGS/math/matrix.h"
#include "NGS/math/rectangle.h"

NGS_BEGIN

template<CArithmetic _Number>
struct Transform2D {
public:
	using element_type = _Number;
public:

	const Point2_<element_type>& GetScale() const { return _scale; }
	const Point2_<element_type>& GetOffset() const { return _offset; }
	ngs::float32 GetRotation() const { return _rotation; }

	void SetScale(element_type x, element_type y) { _scale.Set(x, y); _matrix.Scale(x, y); }
	void SetOffset(element_type x, element_type y) { _offset.Set(x, y); _matrix.Translate(x, y); }
	void SetRotation(ngs::float32 rotation) { _rotation = rotation; _matrix.Rotate(rotation); }
private:
	Matrix<element_type> _matrix = {};
	Point2_<element_type> _scale = {};
	Point2_<element_type> _offset = {};
	ngs::float32 _rotation = {};
};

NGS_END
