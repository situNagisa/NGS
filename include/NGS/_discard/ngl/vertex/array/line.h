#pragma once

#include "NGS/ngl/vertex/array/indices.h"
#include "NGS/ngl/vertex/ctrl/line.h"

NGL_BEGIN
NGL_OBJ_BEGIN

_NGL_VAO_DERIVED_FROM(IndicesVertexArray, LineVertexArray) {
public:
	using base = IndicesVertexArray<_Buffers...>;
	using element_type = typename base::element_type;

	_LineVertexArray(_LineVertexArray&&) = default;
	_LineVertexArray(size_t count, Usage usage)
		: base(count, usage, std::make_shared<LineIndicesCtrl>(count, usage))
	{
		NGS_ASSERT(count > 1);
		base::SetDrawMode(DrawMode::lines);
	}
public:
	template<CBufferRange<element_type> _BufRng>
	void AddBrokenLine(size_t count, _BufRng && buffers) {
		base::AddVertexes(count, std::forward<_BufRng>(buffers));
	}
	void AddBrokenLine(CVertexRange<element_type> auto && vertexes, size_t count) {
		base::AddVertexes(std::forward<decltype(vertexes)>(vertexes), count);
	}
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_T(buffers, base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_VIEW(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_CONTAINER(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	void AddLine(_NGL_VAO_BUF_T(buffers, base) buffers) { AddPolygon(2, buffers...); }
	void AddLine(
		_NGL_VAO_BUF_T(buffers, base) start,
		_NGL_VAO_BUF_T(buffers, base) end
	) {
		std::array<std::array<typename base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(start))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(end))... },
			}};
		AddBrokenLine(points, 2);
	}
	void AddLine(
		_NGL_VAO_BUF_VIEW(base) start,
		_NGL_VAO_BUF_VIEW(base) end
	) {
		std::array<std::array<typename base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(start)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(end)))... },
			}};
		AddBrokenLine(points, 2);
	}
	void AddLine(
		_NGL_VAO_BUF_CONTAINER(base) start,
		_NGL_VAO_BUF_CONTAINER(base) end
	) {
		std::array<std::array<typename base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(start)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(end)))... },
			}};
		AddBrokenLine(points, 2);
	}
};

NGS_END
NGL_END
