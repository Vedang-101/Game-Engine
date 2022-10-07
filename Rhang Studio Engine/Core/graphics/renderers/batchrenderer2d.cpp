#include "batchrenderer2d.h"

namespace rse {
	namespace graphics {

		BatchRenderer2D::BatchRenderer2D() {
			init();
		}
		
		BatchRenderer2D::~BatchRenderer2D() {
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::init() {

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TEX_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
			
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			delete[] indices;

			glBindVertexArray(0);

			m_VertexStructure[0] = maths::vec3( 0.0f,  0.0f, 1.0f);
			m_VertexStructure[1] = maths::vec3( 1.0f,  0.0f, 1.0f);
			m_VertexStructure[2] = maths::vec3( 1.0f,  1.0f, 1.0f);
			m_VertexStructure[3] = maths::vec3( 0.0f,  1.0f, 1.0f);
		}

		void BatchRenderer2D::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}
		
		void BatchRenderer2D::submit(const Renderable2D* renderable, const transform::Transform& transform) {
			const maths::mat4& transformMatrix = transform.transformMatrix;
			const unsigned int color = renderable->getColor();
			const std::vector<maths::vec2> uvs = renderable->getUVs();
			const GLuint tid = renderable->getTID();

			float ts = 0.0f;
			if (tid > 0) {
				bool found = false;
				for (unsigned int i = 0; i < m_TextureSlots.size(); i++) {
					if (m_TextureSlots[i] == tid) {
						ts = (float)(i + 1);
						found = true;
						break;
					}
				}
				if(!found) {
					if (m_TextureSlots.size() >= RENDERER_TEXTURE_SLOTS) {
						end();
						flush();
						begin();
					}
					m_TextureSlots.push_back(tid);
					ts = (float)(m_TextureSlots.size() - 1);
				}
			}
			
			m_Buffer->vertex = ((*m_TransformationBack) * transformMatrix) * m_VertexStructure[0];
			m_Buffer->uv = uvs[0];
			m_Buffer->color = color;
			m_Buffer->tid = ts;
			m_Buffer++;

			m_Buffer->vertex = ((*m_TransformationBack) * transformMatrix) * m_VertexStructure[1];
			m_Buffer->uv = uvs[1];
			m_Buffer->color = color;
			m_Buffer->tid = ts;
			m_Buffer++;

			m_Buffer->vertex = ((*m_TransformationBack) * transformMatrix) * m_VertexStructure[2];
			m_Buffer->uv = uvs[2];
			m_Buffer->color = color;
			m_Buffer->tid = ts;
			m_Buffer++;

			m_Buffer->vertex = ((*m_TransformationBack) * transformMatrix) * m_VertexStructure[3];
			m_Buffer->uv = uvs[3];
			m_Buffer->color = color;
			m_Buffer->tid = ts;
			m_Buffer++;

			m_IndicesCount += 6;
		}

		void BatchRenderer2D::drawString(const std::string& text, const maths::vec3& position, const unsigned int color, const Font& font, float size) {
			using namespace ftgl;

			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				if (m_TextureSlots[i] == font.getTID()) {
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found) {
				if (m_TextureSlots.size() >= 32) {
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(font.getTID());
				ts = (float)(m_TextureSlots.size() - 1);
			}

			float scaleX = m_Width / (m_ProjectionWidth * size);
			float scaleY = m_Height / (m_ProjectionHeight * size);

			float x = position.x;

			texture_font_t* FTfont = font.getFTfont();

			for (int i = 0; i < text.length(); i++) {
				const char& c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(FTfont, c);
				if (glyph) {
					if (i > 0) {
						float kerning = texture_glyph_get_kerning(glyph, text[i-1]);
						x += kerning / scaleX;
					}

					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = (*m_TransformationBack) * maths::vec3(x0, y0, 0);
					m_Buffer->uv = maths::vec2(u0, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = (*m_TransformationBack) * maths::vec3(x0, y1, 0);
					m_Buffer->uv = maths::vec2(u0, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = (*m_TransformationBack) * maths::vec3(x1, y1, 0);
					m_Buffer->uv = maths::vec2(u1, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = (*m_TransformationBack) * maths::vec3(x1, y0, 0);
					m_Buffer->uv = maths::vec2(u1, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_IndicesCount += 6;

					x += glyph->advance_x / scaleX;
				}
			}
		}

		void BatchRenderer2D::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
		void BatchRenderer2D::flush() {
			for (unsigned int i = 0; i < m_TextureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();
			
			glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndicesCount = 0;
		}

	}
}