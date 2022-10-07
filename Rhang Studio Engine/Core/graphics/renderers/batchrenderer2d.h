#pragma once

#include <cstddef>
#include "renderer2d.h"
#include "../renderables/rendererable2d.h"
#include "../buffers/indexbuffer.h"

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TEX_INDEX 2
#define SHADER_COLOR_INDEX 3

namespace rse {
	namespace graphics {
		
		#define RENDERER_TEXTURE_SLOTS	10
		
		class BatchRenderer2D : public Renderer2D {
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_IndicesCount;
			VertexData* m_Buffer;
			maths::vec3 m_VertexStructure[4];

			std::vector<GLuint> m_TextureSlots;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;

			void submit(const Renderable2D* renderable, const transform::Transform& transform) override;
			void drawString(const std::string& text, const maths::vec3& position, const unsigned int color, const Font& font, float size) override;
			void end() override;
			void flush() override;
		private:
			void init();
		};

	}
}