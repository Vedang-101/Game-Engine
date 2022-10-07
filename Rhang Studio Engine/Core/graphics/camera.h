#pragma once

#include "../maths/maths.h"
#include "renderers/batchrenderer2d.h"

namespace rse {
	namespace graphics {
		class Camera {
		private:
			maths::vec3 m_Position;
			float m_Rot;
			maths::mat4 m_ViewMatrix;
			maths::mat4 m_ProjectionMatrix;
			int m_Width, m_Height;
			Renderer2D* m_Renderer;

		public:
			Camera(int width, int height);
			Camera(int width, int height, maths::vec3 pos, float rotation = 0);
			~Camera();

			void setProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
				m_ProjectionMatrix = maths::mat4::orthographic(left, right, bottom, top, nearPlane, farPlane);
				m_Renderer->setWidth(m_Width);
				m_Renderer->setHeight(m_Height);

				m_Renderer->setProjectionWidth(right - left);
				m_Renderer->setProjectionHeight(top - bottom);
			}
			
			void setPosition(maths::vec3 pos) {
				m_Position = pos;
				m_ViewMatrix.updateTransform(m_Position, m_Rot, maths::vec3(1, 1, 1));
			}

			void setRotation(float angle) {
				m_Rot = angle;
				m_ViewMatrix.updateTransform(m_Position, m_Rot, maths::vec3(1, 1, 1));
			}

			inline const maths::vec3& getPosition() const { return m_Position; }
			inline const float getRotation() const { return m_Rot; }
			inline const maths::mat4& getTransform() const { return m_ViewMatrix; }
			inline const maths::mat4& getProjection() const { return m_ProjectionMatrix; }
			inline Renderer2D* getRenderer() const { return m_Renderer; }
		};
	}
}