#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/object.h"
#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/shader/shader.h"
#include "NGS/ngl/vertex/trait.h"
#include "NGS/ngl/vertex/concepts.h"

NGL_BEGIN

NGL_OBJ_BEGIN
class NGS_API  VertexArrayBase;
NGS_END

NGL_TARGET_BEGIN

class NGS_API  VertexArray : public Target < VertexArray, objects::VertexArrayBase > {
	friend class  Target < VertexArray, objects::VertexArrayBase >;
	static void _Select(state_type* state);
};

NGS_END

NGL_OBJ_BEGIN

class NGS_API  VertexArrayBase : public Object {
	NGS_menvironment(VertexArrayBase);
public:
	using element_type = byte;
	using tag_attrib = tag::Attrib<byte>;
	using tag_buffer = tag::Buffer<byte>;
	using tag_vertex = tag::Vertex<byte>;
	using tag_array = tag::Array<byte>;

	VertexArrayBase(buffers::Vertex&& vertex)
		: _vertex(std::move(vertex))
	{
		NGL_CHECK(glGenVertexArrays(1, &_context));
		_vertex.SetVertexArray(this);
	}

	VertexArrayBase(VertexArrayBase&& other) noexcept
		: Object(std::move(other))
		, _draw_mode(other._draw_mode)
		, _vertex(std::move(other._vertex))
		, _offset(other._offset)
		, _count(other._count)
	{}
	virtual ~VertexArrayBase() override
	{
		if (!_context)return;
		NGL_CHECK(glDeleteVertexArrays(1, &_context));
	}

	virtual void Update() override {
		if (!_required_update)return;
		Object::Update();
		_vertex.Update();
	}
	virtual void Render() {
		if (!is_bind(this))
			bind(this);
		NGL_CHECK(glDrawArrays((GLenum)_draw_mode, _offset, _count));
	}
protected:
	template<class  T>
		requires std::ranges::forward_range<T> || std::is_pointer_v<T>
	static auto _GET_BEGIN(T && range, size_t constrain_size = 0) {
		if constexpr (std::ranges::forward_range<decltype(range)>) {
			if constexpr (std::ranges::sized_range<decltype(range)>) {
				NGS_DEBUG_EXPR(if (constrain_size) { NGS_ASSERT(std::ranges::size(range) >= constrain_size); });
			}
			return std::ranges::cbegin(range);
		}
		else if constexpr (std::is_pointer_v<decltype(range)>) {
			return range;
		}
	}
public:
	/**
	 * @brief 添加顶点
	 *
	 * @param buffers 缓存范围（单向范围）
	 * @param count 顶点数量
	 *
	 * @note 缓存范围的长度必须等于顶点缓存的长度
	 */
	template<CBufferRange<element_type> _BufRng>
	void AddVertexes(size_t count, _BufRng&& buffers) {
		NGS_ASSERT(std::ranges::size(buffers) >= _vertex.GetBufferCount(), "buffers size out of range!");
		auto it = _GET_BEGIN(std::forward<_BufRng>(buffers), _vertex.GetBufferCount());
		for (size_t i = 0; i < _vertex.GetBufferCount(); i++)
		{
			auto& buffer = _vertex[i];
			buffer.Write(*it, count, _count);
			++it;
		}
		_count += count;
		RequiredUpdate();
	}
	/**
	 * @brief 添加顶点，添加的数量取决于顶点范围的长度
	 *
	 * @param vertexes 顶点范围（单向范围），元素为缓存范围，或者缓存指针
	 *
	 * @note 缓存范围的长度必须等于顶点缓存的长度
	 */
	void AddVertexes(CVertexRange<element_type> auto&& vertexes, size_t count = 0) {
		if constexpr (!std::ranges::sized_range<decltype(vertexes)>) {
			NGS_ASSERT(count);
		}
		size_t vertex_count = count ? count : std::ranges::size(vertexes);
		auto v_it = _GET_BEGIN(vertexes);
		for (size_t j = 0; j < vertex_count; j++)
		{
			const auto& vertex = *v_it;
			auto it = _GET_BEGIN(vertex, _vertex.GetBufferCount());
			for (size_t i = 0; i < _vertex.GetBufferCount(); i++) {
				auto& buffer = _vertex[i];
				buffer.Write(*it, 1, _count);
				++it;
			}
			_count++;
			++v_it;
		}
		RequiredUpdate();
	}

	void     SetDrawMode(DrawMode mode) { _draw_mode = static_cast<GLenum>(mode); }
	DrawMode GetDrawMode()const { return static_cast<DrawMode>(_draw_mode); }

	virtual void Clear() { _count = 0; }

	byte_ptr GetAttrib(size_t attrib_index, size_t vertex_index) {
		auto [data, format, buffer] = _vertex.GetAttrib(attrib_index);
		data += buffer->format.size * vertex_index;
		return data;
	}
	auto& GetVertexFormat() { return _vertex; }
	const auto& GetVertexFormat()const { return _vertex; }

	bool IsEmpty()const { return !_count; }

	size_t GetCount()const { return _count; }
protected:
	GLenum _draw_mode = GL_POINTS;
	buffers::Vertex _vertex;
	size_t _offset = 0;
	size_t _count = 0;
};

NGS_END

NGS_GL_GET_TARGET_FUNCTION(targets::VertexArray, objects::VertexArrayBase, vertex_array);

NGL_END
