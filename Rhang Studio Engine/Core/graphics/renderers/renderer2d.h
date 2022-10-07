#pragma once

#include <vector>
#include <GL/glew.h>
#include "../../maths/maths.h"
#include "../../transform/transform.h"
#include "../../utils/logger.h"
#include "../font/font.h"



namespace rse {
	namespace graphics {

		class Renderable2D;

		class Renderer2D {
		protected:
			std::vector<maths::mat4> m_TrasformationStack;
			const maths::mat4* m_TransformationBack;
			float m_Width, m_Height, m_ProjectionWidth, m_ProjectionHeight;
		protected:
			Renderer2D() {
				m_TrasformationStack.push_back(maths::mat4::identity());
				m_TransformationBack = &m_TrasformationStack.back();
			}
		public:
			void push(const maths::mat4& matrix, bool override = false) {
				if(override)
					m_TrasformationStack.push_back(matrix);
				else
					m_TrasformationStack.push_back(m_TrasformationStack.back() * matrix);
				m_TransformationBack = &m_TrasformationStack.back();
			}

			void setWidth(float width) { m_Width = width; }
			void setHeight(float height) { m_Height = height; }
			void setProjectionWidth(float width) { m_ProjectionWidth = width; }
			void setProjectionHeight(float height) { m_ProjectionHeight = height; }

			void pop() {
				if (m_TrasformationStack.size() > 1)
					m_TrasformationStack.pop_back();
				else
					utils::LogError("Nothing left to pop from transformation stack");
				m_TransformationBack = &m_TrasformationStack.back();
			}

			virtual void submit(const Renderable2D* renderable, const transform::Transform& transform) = 0;
			virtual void drawString(const std::string& text, const maths::vec3& position, const unsigned int color, const Font& font, float size) {}
			virtual void flush() = 0;
			virtual void begin() {}
			virtual void end() {}
		};

	}
}