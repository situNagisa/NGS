#pragma once

#include "NGS/ngl/vertex/array/indices.h"

NGL_BEGIN
NGL_OBJ_BEGIN

_NGL_VAO_DERIVED_FROM(IndicesVertexArray, LineVertexArray) {
public:
	using base = IndicesVertexArray<_Buffers...>;
	using element_type = typename base::element_type;
	using grandfather = typename base::base;

	_LineVertexArray(_LineVertexArray&&) = default;
	_LineVertexArray(size_t count, Usage usage)
		: base(count, usage, 2 * count)
	{
		NGS_ASSERT(count > 1);
		base::SetDrawMode(DrawMode::lines);
	}

private:
	void _AddBrokenLine(size_t count) {
		NGS_ASSERT(count > 1);
		std::vector<indices_t> indices{};
		for (indices_t i = base::_indices_count; i < base::_indices_count + count - 1; ++i) {
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		base::_AddIndices(indices);
	}
public:
	template<CBufferRange<element_type> _BufRng>
	void AddBrokenLine(size_t count, _BufRng && buffers) {
		grandfather::AddVertexes(count, std::forward<_BufRng>(buffers));
		_AddBrokenLine(count);
	}
	void AddBrokenLine(CVertexRange<element_type> auto && vertexes, size_t count) {
		grandfather::AddVertexes(std::forward<decltype(vertexes)>(vertexes), count);
		_AddBrokenLine(count);
	}
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_T(buffers, base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_VIEW(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	void AddBrokenLine(size_t count, _NGL_VAO_BUF_CONTAINER(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	void AddLine(_NGL_VAO_BUF_T(buffers, base) buffers) { AddPolygon(2, buffers); }
	void AddLine(
		_NGL_VAO_BUF_T(buffers, base) start,
		_NGL_VAO_BUF_T(buffers, base) end
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(start))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(end))... },
			}};
		AddBrokenLine(points, 2);
	}
	void AddLine(
		_NGL_VAO_BUF_VIEW(base) start,
		_NGL_VAO_BUF_VIEW(base) end
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(start)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(end)))... },
			}};
		AddBrokenLine(points, 2);
	}
	void AddLine(
		_NGL_VAO_BUF_CONTAINER(base) start,
		_NGL_VAO_BUF_CONTAINER(base) end
	) {
		std::array<std::array<base::tag_buffer::type, base::buffer_count>, 2> points{{
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(start)))...},
			{ std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(end)))... },
			}};
		AddBrokenLine(points, 2);
	}
};

NGS_END
NGL_END
