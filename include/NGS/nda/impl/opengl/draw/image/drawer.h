#pragma once

#include "NGS/nda/impl/opengl/defined.h"
#include "NGS/nda/impl/opengl/draw/image/unit.h"

NDA_IMPL_OPENGL_BEGIN

struct NGS_API TextureDrawer {
	using buffer_pos = ngl::buffer_c<ngs::float32, 2>;
	using buffer_size = ngl::buffer_c<ngs::float32, 2>;
	using buffer_texture_slot = ngl::buffer_c<ngs::float32, 1>;

	using vertex_array_polygon_t = ngl::objects::VertexArray<buffer_pos, buffer_size, buffer_texture_slot>;

	constexpr static size_t texture_capacity = 16;
	constexpr static size_t vertex_capacity = 4 * texture_capacity;

	TextureDrawer(std::string_view vertex, std::string_view fragment, std::string_view geometry)
	{
		renderer.SetVertexArray(std::make_shared<vertex_array_polygon_t>(vertex_capacity, ngl::Usage::static_draw));
		renderer.SetShader(std::make_shared<ngl::objects::Shader>("projection_matrix", "texture_transform", "frag_texture_simples"));
		renderer.SetBackgroundColor(ngs::ARGB32{ 0xFF, 0x33, 0x55, 0x55 });

		auto& shader = *renderer.GetShader();

		shader.CompileAndLink(vertex, fragment, geometry);

		ngl::OpenGL::I().shader->Select(shader);
		int samplers[] = { 0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
		NGL_CHECK(glUniform1iv(shader.GetUniformLocation("frag_texture_simples"), sizeof(samplers) / sizeof(samplers[0]), samplers));
	}

	void AddTexture(ImageDrawUnit& target, const ngs::Point2f& pos) {
		if (!target.GetBitmap()->bitmap_data)return;

		auto& polygon = *std::dynamic_pointer_cast<vertex_array_polygon_t>(renderer.GetVertexArray());
		auto& texture = *target.texture;

		ngs::float32 texture_count = targets.size();

		polygon.AddVertexes(1,
			{ pos.x,pos.y },
			{ (ngs::float32)texture.GetImage().GetSize().x ,(ngs::float32)texture.GetImage().GetSize().y },
			{ texture_count }
		);
		texture.slot = ngl::TextureSlot::_0 + texture_count;

		targets.push_back(&target);
	}
	void Render() {
		auto& shader = *renderer.GetShader();
		{
			ngl::OpenGL::I().shader->Select(shader);
			mla::Matrix<matrix_t::dimension, matrix_t::dimension, matrix_t::element_type> data = mla::transpose(matrix);
			NGL_CHECK(glUniformMatrix3fv(shader.GetUniformLocation("projection_matrix"), 1, GL_FALSE, &data(0, 0)));
		}

		for (size_t i = 0; i < targets.size(); i++)
		{
			auto& target = targets[i];
			target->Render();
			mla::Matrix<matrix_t::dimension, matrix_t::dimension, matrix_t::element_type> data = mla::transpose(target->matrix);
			NGL_CHECK(glUniformMatrix3fv(shader.GetUniformLocation("texture_transform") + i, 1, GL_FALSE, &data(0, 0)));
		}

		renderer.Render();
		Clear();
	}
	void Clear() {
		targets.clear();
	}

	matrix_t matrix = mla::identity_matrix_v<3, float>;
	std::vector<ImageDrawUnit*> targets{};
	ngl::Renderer renderer;
};

NDA_IMPL_OPENGL_END
