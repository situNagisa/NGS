#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

class NGS_API IGraphic {
public:
	virtual ~IGraphic() = default;

	virtual void DrawPoint(const circle_type& circle) {}
	virtual void DrawCircle(const circle_type& circle) {}
	virtual void DrawEllipse(const point_type& position, const arithmetic_type width, const arithmetic_type height) {}

	virtual void DrawRectangle(const rectangle_type& rectangle) {}
	virtual void DrawRectangle(const rectangle_type& rectangle, const arithmetic_type radius) {}
	virtual void DrawRectangle(const rectangle_type& rectangle, const arithmetic_type ellipse_width, const arithmetic_type ellipse_height) {}

	virtual void SetColor(const color_type color) {}
	virtual void DrawBrokenLine(const point_type* vertexes, size_t count) {}
	virtual void DrawPolygon(const point_type* vertexes, size_t count) {}

	virtual void DrawLine(const point_type& start, const point_type& end) {}

	template<class _Rng>
		requires std::ranges::random_access_range<_Rng>&& std::convertible_to<std::ranges::range_value_t<_Rng>, point_type>
	void DrawBrokenLine(const _Rng& range) {
		DrawBrokenLine(std::ranges::cdata(range), std::ranges::size(range));
	}
	template<class _Rng>
		requires std::ranges::random_access_range<_Rng>&& std::convertible_to<std::ranges::range_value_t<_Rng>, point_type>
	void DrawPolygon(const _Rng& range) {
		DrawPolygon(std::ranges::cdata(range), std::ranges::size(range));
	}
};

NGS_DL_END
