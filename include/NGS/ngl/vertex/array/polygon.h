#pragma once

#include "NGS/ngl/vertex/array/indices.h"

NGL_BEGIN
NGL_OBJ_BEGIN

_NGL_VAO_DERIVED_FROM(IndicesVertexArray, PolygonVertexArray) {
public:
	using base = IndicesVertexArray<_Buffers...>;
	using element_type = typename base::element_type;
	using grandfather = typename base::base;

	_PolygonVertexArray(_PolygonVertexArray&&) = default;
	_PolygonVertexArray(size_t count, Usage usage)
		: base(count, usage, 3 * (count - 2)) {
		NGS_ASSERT(count > 2);
		base::SetDrawMode(DrawMode::triangles);
	}
private:
	void _AddPolygon(size_t count) {
		NGS_ASSERT(count > 2);
		std::vector<indices_t> indices{};
		for (size_t i = base::_indices_count + 1; i < base::_indices_count + count - 1; i++)
		{
			indices.push_back(base::_indices_count);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		base::_AddIndices(indices);
	}
public:
	template<CBufferRange<element_type> _BufRng>
	void AddPolygon(size_t count, _BufRng && buffers) {
		grandfather::AddVertexes(count, std::forward<_BufRng>(buffers));
		_AddPolygon(count);
	}
	void AddPolygon(CVertexRange<element_type> auto && vertexes, size_t count) {
		grandfather::AddVertexes(std::forward<decltype(vertexes)>(vertexes), count);
		_AddPolygon(count);
	}
	void AddPolygon(size_t count, _NGL_VAO_BUF_T(buffers, base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	void AddPolygon(size_t count, _NGL_VAO_BUF_VIEW(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	void AddPolygon(size_t count, _NGL_VAO_BUF_CONTAINER(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	void AddTriangle(_NGL_VAO_BUF_T(buffers, base) buffers) { AddPolygon(3, buffers); }
	void AddTriangle(
		_NGL_VAO_BUF_T(buffers, base) p0,
		_NGL_VAO_BUF_T(buffers, base) p1,
		_NGL_VAO_BUF_T(buffers, base) p2
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 3> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(p0))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(p1))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(p2))... },
			}};
		AddPolygon(points, 3);
	}
	void AddTriangle(
		_NGL_VAO_BUF_VIEW(base) p0,
		_NGL_VAO_BUF_VIEW(base) p1,
		_NGL_VAO_BUF_VIEW(base) p2
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 3> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p0)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p1)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p2)))... },
			}};
		AddPolygon(points, 3);
	}
	void AddTriangle(
		_NGL_VAO_BUF_CONTAINER(base) p0,
		_NGL_VAO_BUF_CONTAINER(base) p1,
		_NGL_VAO_BUF_CONTAINER(base) p2
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 3> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p0)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p1)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(p2)))... },
			}};
		AddPolygon(points, 3);
	}

	void AddQuad(_NGL_VAO_BUF_T(buffers, base) buffers) { AddPolygon(4, buffers); }
	void AddQuad(
		_NGL_VAO_BUF_T(buffers, base) left_top,
		_NGL_VAO_BUF_T(buffers, base) right_top,
		_NGL_VAO_BUF_T(buffers, base) right_bottom,
		_NGL_VAO_BUF_T(buffers, base) left_bottom
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 4> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(left_top))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(right_top))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(right_bottom))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(left_bottom))... },
			}};
		AddPolygon(points, 4);
	}
	void AddQuad(
		_NGL_VAO_BUF_VIEW(base) left_top,
		_NGL_VAO_BUF_VIEW(base) right_top,
		_NGL_VAO_BUF_VIEW(base) right_bottom,
		_NGL_VAO_BUF_VIEW(base) left_bottom
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 4> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(left_top)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(right_top)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(right_bottom)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(left_bottom)))... },
			}};
		AddPolygon(points, 4);
	}
	void AddQuad(
		_NGL_VAO_BUF_CONTAINER(base) left_top,
		_NGL_VAO_BUF_CONTAINER(base) right_top,
		_NGL_VAO_BUF_CONTAINER(base) right_bottom,
		_NGL_VAO_BUF_CONTAINER(base) left_bottom
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 4> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(left_top)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(right_top)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(right_bottom)))... },
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(left_bottom)))... },
			}};
		AddPolygon(points, 4);
	}
};

NGS_END
NGL_END
