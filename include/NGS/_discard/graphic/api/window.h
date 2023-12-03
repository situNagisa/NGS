#pragma once

#include "NGS/extend/extend.h"

NGS_BEGIN


template<class  T>
concept CWindow = requires(T t, const T t_cst) {
	{ t("name", Point2i(0, 0)) };
	{ t("name", Rectanglei(0, 0, 0, 0)) };
	{ t_cst.ShouldClose() } -> std::convertible_to<bool>;
	{ t_cst.IsPress(0) } -> std::convertible_to<bool>;
	{ t_cst.IsRelease(0) } -> std::convertible_to<bool>;
	{ t.SetTitle("") };
	{ t.SetPosition(0, 0) };
	{ t.SetSize(0, 0) };
	{ t.SetBounds(0, 0, 0, 0) };
	{ t.SetLimits(0, 0, 0, 0) };
	{ t_cst.GetFramebufferSize() } -> std::convertible_to<Point2i>;
	{ t_cst.GetPosition() } -> std::convertible_to<Point2i>;
	{ t_cst.GetSize() } -> std::convertible_to<Point2i>;
	{ t_cst.GetBounds() } -> std::convertible_to<Rectanglei>;
	{ t.Iconify() };
	{ t.Restore() };
	{ t.Maximize() };
	{ t.Show() };
	{ t.Hide() };
};


NGS_END
