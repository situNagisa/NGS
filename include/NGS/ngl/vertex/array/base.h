#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/object.h"
#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/shader/shader.h"
#include "NGS/ngl/vertex/trait.h"

NGL_BEGIN

NGL_OBJ_BEGIN
class VertexArrayBase;
NGS_END

NGL_TARGET_BEGIN

class VertexArray : public Target < VertexArray, objects::VertexArrayBase > {
	friend class base;
	static void _Select(state_type* state);
};

NGS_END

NGL_OBJ_BEGIN

class VertexArrayBase : public Object {
public:
	using element_type = byte;
	using tag_attrib = tag::Attrib<byte>;
	using tag_buffer = tag::Buffer<byte>;
	using tag_vertex = tag::Vertex<byte>;
	using tag_array = tag::Array<byte>;

	VertexArrayBase(buffers::Vertex&& vertex)
		: _vertex(std::move(vertex))
	{
		_NGL_CHECK(glGenVertexArrays(1, &_context));
		_vertex.SetVertexArray(this);
	}

	VertexArrayBase(VertexArrayBase&& other)
		: Object(std::move(other))
		, _vertex(std::move(other._vertex))
		, _draw_mode(other._draw_mode)
		, _offset(other._offset)
		, _count(other._count)
	{}
	virtual ~VertexArrayBase() {
		if (!_context)return;
		_NGL_CHECK(glDeleteVertexArrays(1, &_context));
	}

	virtual void Update() override {
		if (!_required_update)return;
		Object::Update();
		_vertex.Update();
	}
	virtual void Render() {
		NGS_ASSERT(OpenGL::I().vertex_array->IsState(this));
		if (_current_shader)
			OpenGL::I().shader->Select(_current_shader);
		_NGL_CHECK(glDrawArrays((GLenum)_draw_mode, _offset, _count));
	}
protected:
	template<class T>
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
			it++;
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
				it++;
			}
			_count++;
			v_it++;
		}
		RequiredUpdate();
	}

	void SetDrawMode(DrawMode mode) { _draw_mode = (GLenum)mode; }
	void SetShader(Shader& shader) { SetShader(&shader); }
	void SetShader(Shader* shader) { _current_shader = shader; }

	virtual void Clear() { _count = 0; }

	byte_ptr GetAttrib(size_t attrib_index, size_t vertex_index) {
		auto [data, format, buffer] = _vertex.GetAttrib(attrib_index);
		data += buffer->format.size * vertex_index;
		return data;
	}
	auto& GetVertexFormat() { return _vertex; }
	const auto& GetVertexFormat()const { return _vertex; }
protected:
	GLenum _draw_mode = GL_POINTS;
	buffers::Vertex _vertex;
	size_t _offset = 0;
	size_t _count = 0;
	Shader* _current_shader = nullptr;
};

NGS_END
NGL_END
