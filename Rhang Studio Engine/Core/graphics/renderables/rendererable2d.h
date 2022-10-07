#pragma once

#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"

#include "../renderers/renderer2d.h"

#include "../textures/texture.h"
#include "../../maths/maths.h"
#include "../shader.h"

#include "../../transform/transform.h"

namespace rse {
	namespace graphics {

		struct VertexData {
			maths::vec3 vertex;
			maths::vec2 uv;
			float tid;
			unsigned int color;
		};

		class Renderable2D {
		protected:
			transform::Transform m_Transform;
			unsigned int m_Color;
			std::vector<maths::vec2> m_UV;
			Texture* m_Texture;
		protected:
			Renderable2D() : m_Texture(nullptr) { setDefaultUV(); }
		public:
			Renderable2D(unsigned int color)
				: m_Color(color), m_Texture(nullptr)
			{
				setDefaultUV();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const {
				renderer->submit(this, m_Transform);
			}

			inline const unsigned int getColor() const { return m_Color; }
			void setColor(unsigned int color) { m_Color = color; }
			void setColor(const maths::vec4& color) {
				int r = int(color.x * 255.0f);
				int g = int(color.y * 255.0f);
				int b = int(color.z * 255.0f);
				int a = int(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			void setTexture(Texture* texture) { m_Texture = texture; }
			
			inline const std::vector<maths::vec2>& getUVs() const { return m_UV; }
			inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }

			void setSprite(int index) {
				float x, y, w, h;
				if (m_Texture) {
					m_Texture->getUV(index, &x, &y, &w, &h);
					m_UV[0] = maths::vec2(x + 0, y + 0);
					m_UV[1] = maths::vec2(x + w, y + 0);
					m_UV[2] = maths::vec2(x + w, y + h);
					m_UV[3] = maths::vec2(x + 0, y + h);
				}
			}

			void setTransition(maths::vec2 position) { m_Transform.setPosition(maths::vec3(position.x, position.y, 0)); }
			void setScale(maths::vec2 scale) { m_Transform.setScale({ scale.x, scale.y, 1 }); }
		private:
			void setDefaultUV() {
				m_UV.push_back(maths::vec2(0, 0));
				m_UV.push_back(maths::vec2(1, 0));
				m_UV.push_back(maths::vec2(1, 1));
				m_UV.push_back(maths::vec2(0, 1));
			}
		};
	}
}