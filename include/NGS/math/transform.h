#pragma once

#include "NGS/base/base.h"
#include "NGS/math/matrix.h"
#include "NGS/math/rectangle.h"

NGS_BEGIN

template<Arithmetic _Number>
struct Transform {
public:
	using type = _Number;
public:

	const Point2_<type>& GetScale() const { return _scale; }
	const Point2_<type>& GetOffset() const { return _offset; }
	ngs::float32 GetRotation() const { return _rotation; }
	const Matrix<type>& GetMatrix()const { return _matrix; }

	void SetScale(type x, type y) { _scale.Set(x, y); _matrix.Scale(x, y); }
	void SetOffset(type x, type y) { _offset.Set(x, y); _matrix.Translate(x, y); }
	void SetRotation(ngs::float32 rotation) { _rotation = rotation; _matrix.Rotate(rotation); }
private:
	Matrix<type> _matrix = {};
	Point2_<type> _scale = {};
	Point2_<type> _offset = {};
	ngs::float32 _rotation = {};
};

NGS_END
