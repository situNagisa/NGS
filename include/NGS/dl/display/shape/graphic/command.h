#pragma once

#include "NGS/dl/display/shape/graphic/graphic.h"
#include "NGS/dl/enum/graphic_command.h"

NGS_DL_BEGIN

struct NGS_API GraphicPath : public IGraphic {
private:
	using base_type = IGraphic;
public:
	GraphicPath() = default;
	virtual ~GraphicPath() override = default;

	virtual void DrawPoint(const ndl::circle_type& circle) override;
	virtual void DrawCircle(const ndl::circle_type& circle) override;
	virtual void DrawEllipse(const point_type& position, const ndl::arithmetic_type width, const ndl::arithmetic_type height) override;

	virtual void DrawRectangle(const ndl::rectangle_type& rectangle) override;
	virtual void DrawRectangle(const ndl::rectangle_type& rectangle, const ndl::arithmetic_type radius) override;
	virtual void DrawRectangle(const ndl::rectangle_type& rectangle, const ndl::arithmetic_type ellipse_width, const ndl::arithmetic_type ellipse_height) override;

	virtual void SetColor(const color_type color) override;
	virtual void DrawBrokenLine(const ndl::point_type* vertexes, size_t count) override;
	virtual void DrawPolygon(const ndl::point_type* vertexes, size_t count) override;

	using base_type::DrawBrokenLine;
	using base_type::DrawPolygon;
public:
	std::vector<GraphicPathCommand> commands{};
	std::vector<arithmetic_type> parameters{};
};

NGS_DL_END
