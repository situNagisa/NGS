#pragma once

#include "NGS/dl/display/shape/graphic/command.h"

NGS_DL_BEGIN

NGS_HPP_INLINE void GraphicPath::DrawPoint(const ndl::circle_type& circle)
{
	commands.push_back(GraphicPathCommand::point);
	parameters.push_back(circle.position.x);
	parameters.push_back(circle.position.y);
	parameters.push_back(circle.radius);
}

NGS_HPP_INLINE void GraphicPath::DrawCircle(const ndl::circle_type& circle)
{
	commands.push_back(GraphicPathCommand::circle);
	parameters.push_back(circle.position.x);
	parameters.push_back(circle.position.y);
	parameters.push_back(circle.radius);
}

NGS_HPP_INLINE void GraphicPath::DrawEllipse(const point_type& position, const ndl::arithmetic_type width, const ndl::arithmetic_type height)
{
	commands.push_back(GraphicPathCommand::ellipse);
	parameters.push_back(position.x);
	parameters.push_back(position.y);
	parameters.push_back(width);
	parameters.push_back(height);
}

NGS_HPP_INLINE void GraphicPath::DrawRectangle(const ndl::rectangle_type& rectangle)
{
	commands.push_back(GraphicPathCommand::rectangle);
	parameters.push_back(rectangle.x);
	parameters.push_back(rectangle.y);
	parameters.push_back(rectangle.width);
	parameters.push_back(rectangle.height);
}

NGS_HPP_INLINE void GraphicPath::DrawRectangle(const ndl::rectangle_type& rectangle, const ndl::arithmetic_type radius)
{
	commands.push_back(GraphicPathCommand::rectangle_round_circle);
	parameters.push_back(rectangle.x);
	parameters.push_back(rectangle.y);
	parameters.push_back(rectangle.width);
	parameters.push_back(rectangle.height);
	parameters.push_back(radius);
}

NGS_HPP_INLINE void GraphicPath::DrawRectangle(const ndl::rectangle_type& rectangle, const ndl::arithmetic_type ellipse_width, const ndl::arithmetic_type ellipse_height)
{
	commands.push_back(GraphicPathCommand::rectangle_round_ellipse);
	parameters.push_back(rectangle.x);
	parameters.push_back(rectangle.y);
	parameters.push_back(rectangle.width);
	parameters.push_back(rectangle.height);
	parameters.push_back(ellipse_width);
	parameters.push_back(ellipse_height);
}

NGS_HPP_INLINE void GraphicPath::SetColor(const color_type color)
{
	commands.push_back(GraphicPathCommand::color);
	parameters.push_back(color.AlphaPercent());
	parameters.push_back(color.RedPercent());
	parameters.push_back(color.GreenPercent());
	parameters.push_back(color.BluePercent());
}

NGS_HPP_INLINE void GraphicPath::DrawBrokenLine(const ndl::point_type* vertexes, size_t count)
{
	commands.push_back(GraphicPathCommand::broken_line);
	parameters.push_back(static_cast<arithmetic_type>(count));
	for (size_t i = 0; i < count; ++i)
	{
		parameters.push_back(vertexes[i].x);
		parameters.push_back(vertexes[i].y);
	}
}

NGS_HPP_INLINE void GraphicPath::DrawPolygon(const ndl::point_type* vertexes, size_t count)
{
	commands.push_back(GraphicPathCommand::polygon);
	parameters.push_back(static_cast<arithmetic_type>(count));
	for (size_t i = 0; i < count; ++i)
	{
		parameters.push_back(vertexes[i].x);
		parameters.push_back(vertexes[i].y);
	}
}

NGS_DL_END
